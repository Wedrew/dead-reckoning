//!**********************************************************
//! @file   assets_manager.hpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Collects all the assets inside of the asset folder
//!         from the build directory and stores them for later
//!         use. This class is NOT thread safe.
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#define STB_IMAGE_IMPLEMENTATION

#include <fstream>
#include <iterator>
#include <string_view>
#include <algorithm>

#include "StandAlone/DirStackFileIncluder.h"
#include "StandAlone/ResourceLimits.h"

#include "assets_manager.hpp"

namespace fs = std::filesystem;

namespace Zero {

AssetsManager::AssetsManager() {
    glslang::InitializeProcess();
    recursivelyAcquire(assetsDir);
    compileShaders();
    setImageData();
};

std::shared_ptr<AssetsManager> AssetsManager::getAssetsManager() {
    static std::weak_ptr<AssetsManager> instance;

    if(auto inst = instance.lock()) {
        return inst;
    }

    auto inst = std::shared_ptr<AssetsManager>(new AssetsManager());
    instance = inst;
    return inst;
}


void AssetsManager::recursivelyAcquire(fs::path const &path) {
    if(fs::exists(path) and fs::is_directory(path)) {
        assetsLogger->info("Found assets folder at {}", assetsDir.string());
        for(auto const &file: fs::recursive_directory_iterator(path)) {
            if(not file.is_directory()) {

                std::ifstream fileStream(file.path().string(), std::ios::binary);
                std::string fileContents((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

                if(file.path().parent_path().filename() == "fonts") {
                    fontsFileMap.insert(std::make_pair(file, fileContents));
                    assetsLogger->info("Stored font {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "textures") {
                    imagesFileMap.insert(std::make_pair(file, fileContents));
                    assetsLogger->info("Stored texture {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "shaders") {
                    shadersFileMap.insert(std::make_pair(file, fileContents));
                    assetsLogger->info("Stored shader {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "models") {
                    tinyObjFileMap.insert(std::make_pair(file.path().stem().string(), file.path().string()));
                    assetsLogger->info("Stored model {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "gltf_bin") {
                    gltfFileMap.insert(std::make_pair(file.path().stem().string(), file.path().string()));
                    assetsLogger->info("Stored gltf {}", file.path().filename().string());
                }
            }
        }
    }
}

void AssetsManager::refreshFiles() {
    fontsFileMap.clear();
    imagesFileMap.clear();
    shadersFileMap.clear();
    tinyObjFileMap.clear();
    recursivelyAcquire(assetsDir);
    compileShaders();
    setImageData();
}

void AssetsManager::compileShaders() {
    for(auto const &file : shadersFileMap) {
        compileGLSL(file.first, file.second);
    }
}

void AssetsManager::setImageData() {
    for(auto const &file : imagesFileMap) {
        std::string extension = file.first.extension().string();

        if(std::find(imageTypes.begin(), imageTypes.end(), extension) not_eq imageTypes.end()) {
            int width, height, channels;

            unsigned char *pixels = stbi_load(file.first.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);
            ImageDescription imageDescription = ImageDescription(pixels, static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(4));

            if(not pixels) {
                assetsLogger->info("Failed to load texture image: {}", file.first.filename().string());
                throw std::runtime_error("Failed to load texture image!");
            } else {
                imageData.insert(std::make_pair(file.first.stem().string(), imageDescription));
                assetsLogger->info("Loaded texture image: {}", file.first.filename().string());
            }
        } else {
            assetsLogger->warn("Found an unsupported image file type: {}", file.first.filename().string());
        }
    }
}

void AssetsManager::compileGLSL(fs::path const& file, std::string const& fileString) {
    EShLanguage shaderType = getShaderStage(file.extension().string());
    glslang::TShader shader(shaderType);
    auto inputCString = fileString.c_str();
    shader.setStrings(&inputCString, 1);

    int clientInputSemanticsVersion = 100; // maps to, say, #define VULKAN 100
    glslang::EShTargetClientVersion vulkanClientVersion = glslang::EShTargetVulkan_1_0;
    glslang::EShTargetLanguageVersion targetVersion = glslang::EShTargetSpv_1_0;

    shader.setEnvInput(glslang::EShSourceGlsl, shaderType, glslang::EShClientVulkan, clientInputSemanticsVersion);
    shader.setEnvClient(glslang::EShClientVulkan, vulkanClientVersion);
    shader.setEnvTarget(glslang::EShTargetSpv, targetVersion);

    TBuiltInResource resources = glslang::DefaultTBuiltInResource;
    EShMessages messages = (EShMessages) (EShMsgSpvRules | EShMsgVulkanRules);
    const int defaultVersion = 450;

    DirStackFileIncluder includer;
    includer.pushExternalLocalDirectory(file.parent_path().string());

    std::string preprocessedGLSL;

    if(not shader.preprocess(&resources, defaultVersion, ENoProfile, false, false, messages, &preprocessedGLSL, includer)) {
        assetsLogger->error("GLSL preprocessing failed for: {}", file.filename().string());
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL preprocessing failed");
    } else {
        assetsLogger->debug("GLSL preprocessing succeeded for: {}", file.filename().string());
    }

    const char *preprocessedCStr = preprocessedGLSL.c_str();
    shader.setStrings(&preprocessedCStr, 1);
    glslang::TProgram program;

    if(not shader.parse(&resources, defaultVersion, false, messages)) {
        assetsLogger->error("GLSL parsing failed for: {}", file.filename().string());
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL parsing failed");
    } else {
        assetsLogger->debug("GLSL parsing succeeded for: {}", file.filename().string());
        program.addShader(&shader);
    }

    if(not program.link(messages)) {
        assetsLogger->error("GLSL linking failed");
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL parsing failed");
    } else {
        assetsLogger->debug("GLSL linking succeeded for: {}", file.filename().string());
    }

    std::vector<uint32_t> spirV;
    spv::SpvBuildLogger logger;
    glslang::SpvOptions spvOptions;
    glslang::GlslangToSpv(*program.getIntermediate(shaderType), spirV, &logger, &spvOptions);

    if (logger.getAllMessages().length() > 0) {
        assetsLogger->debug("Spv logger says: {}", logger.getAllMessages());
    }

    spirVModules.insert(std::make_pair(file.filename().string(), spirV));
    assetsLogger->debug("Stored SpirV module: {}", file.filename().string());
}

EShLanguage AssetsManager::getShaderStage(std::string const &stage) {
    if (stage == ".vert") {
        return EShLangVertex;
    } else if (stage == ".tesc") {
        return EShLangTessControl;
    } else if (stage == ".tese") {
        return EShLangTessEvaluation;
    } else if (stage == ".geom") {
        return EShLangGeometry;
    } else if (stage == ".frag") {
        return EShLangFragment;
    } else if (stage == ".comp") {
        return EShLangCompute;
    } else {
        assetsLogger->error("Unknown shader stage");
        return EShLangCount;
    }
}


}