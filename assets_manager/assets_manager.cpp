#include <fstream>
#include <iterator>
#include <string_view>

#include "assets_manager.hpp"
#include "StandAlone/DirStackFileIncluder.h"
#include "StandAlone/ResourceLimits.h"

namespace fs = std::filesystem;

namespace zero {

AssetsManager::AssetsManager() {
    glslang::InitializeProcess();
    recursivelyAcquire(assetsDir);
}

void AssetsManager::recursivelyAcquire(fs::path const &path) {
    // Get all the files in the assets directory
    if(fs::exists(path) and fs::is_directory(path)) {
        assetsLogger->info("Found assets folder at {}", assetsDir.string());
        for(auto const &file: fs::recursive_directory_iterator(path)) {
            if(not file.is_directory()) {

                std::ifstream fileStream(file.path().string(), std::ios::binary);
                std::string fileContents((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

                if(file.path().parent_path().filename() == "fonts") {
                    fontsFileMap.insert(std::pair<fs::path, std::string>(file, fileContents));
                    assetsLogger->info("Stored font {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "images") {
                    imagesFileMap.insert(std::pair<fs::path, std::string>(file, fileContents));
                    assetsLogger->info("Stored image {}", file.path().filename().string());
                } else if(file.path().parent_path().filename() == "shaders") {
                    shadersFileMap.insert(std::pair<fs::path, std::string>(file, fileContents));
                    assetsLogger->info("Stored shader {}", file.path().filename().string());
                }
            }
        }
    }
}

void AssetsManager::refreshFiles() {
    fontsFileMap.clear();
    imagesFileMap.clear();
    shadersFileMap.clear();
    recursivelyAcquire(assetsDir);
}

void AssetsManager::compileShaders(bool optimize) {
    // First preprocess and parse
    for(auto const &file : shadersFileMap) {
        compileGLSL(file.first, file.second);
    }

    // // Next compile the shader
    // for(auto shader : glslangShaders) {
    //     program.addShader(shader);
    // }



}

void AssetsManager::compileGLSL(fs::path const& file, std::string const& fileString) {
    EShLanguage shaderType = getShaderStage(file.extension().string());
    glslang::TShader shader(shaderType);
    auto inputCString = fileString.c_str();
    shader.setStrings(&inputCString, 1);

    int clientInputSemanticsVersion = 100; // maps to, say, #define VULKAN 100
    glslang::EShTargetClientVersion vulkanClientVersion = glslang::EShTargetOpenGL_450;
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
        assetsLogger->error("GLSL preprocessing failed for: {}", file.string());
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL preprocessing failed");
    } else {
        assetsLogger->debug("GLSL preprocessing succeeded for: {}", file.string());
    }

    const char *preprocessedCStr = preprocessedGLSL.c_str();
    shader.setStrings(&preprocessedCStr, 1);
    glslang::TProgram program;

    if(not shader.parse(&resources, defaultVersion, false, messages)) {
        assetsLogger->error("GLSL parsing failed for: {}", file.string());
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL parsing failed");
    } else {
        assetsLogger->debug("GLSL parsing succeeded for: {}", file.string());
        program.addShader(&shader);
    }

    if(not program.link(messages)) {
        assetsLogger->error("GLSL linking failed");
        assetsLogger->error("shader.getInfoLog(): {}", shader.getInfoLog());
        assetsLogger->error("shader.getInfoDebugLog(): {}", shader.getInfoDebugLog());
        throw std::runtime_error("GLSL parsing failed");
    } else {
        assetsLogger->debug("GLSL linking succeeded for: {}", file.string());
    }

    std::vector<uint32_t> spirV;
    spv::SpvBuildLogger logger;
    glslang::SpvOptions spvOptions;
    glslang::GlslangToSpv(*program.getIntermediate(shaderType), spirV, &logger, &spvOptions);

    if (logger.getAllMessages().length() > 0) {
        assetsLogger->debug("Spv logger says: {}", logger.getAllMessages());
    }

    spirVModules.insert(std::pair<std::string, std::vector<uint32_t>>(file.filename().string(), spirV));
    assetsLogger->debug("Stored SpirV module {}", file.filename().string());
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