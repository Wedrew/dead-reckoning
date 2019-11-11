//!**********************************************************
//! @file   assets_manager.hpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Singleton class that collects all the assets inside
//!         of the asset folder from the build directory and
//!         stores them for later use. This class is NOT thread
//!         safe.
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef ASSETS_MANAGER_HPP
#define ASSETS_MANAGER_HPP

#include <string>
#include <filesystem>
#include <map>
#include <vector>

#include "stb_image.h"
#include "fx/gltf.h"
#include "glslang/Public/ShaderLang.h"
#include "SPIRV/GlslangToSpv.h"

#include "image_description.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;
using FileMap = std::map<fs::path, std::string>;
using SpirVMap = std::map<std::string, std::vector<uint32_t>>;

namespace Zero {

class AssetsManager {

public:
    AssetsManager(const AssetsManager&) = delete;
    AssetsManager(AssetsManager&&) = delete;
    AssetsManager& operator=(const AssetsManager&) = delete;
    AssetsManager& operator=(AssetsManager&&) = delete;

    static std::shared_ptr<AssetsManager> getAssetsManager();

    void refreshFiles();

    std::vector<uint32_t> const &getSpirvModules(std::string const &moduleName) {return spirVModules.find(moduleName)->second;};
    std::string const &getTinyObjPath(std::string const &tinyObjName) {return tinyObjFileMap.find(tinyObjName)->second;};
    std::string const &getGltfDocumentPath(std::string const &gltfPath) {return gltfFileMap.find(gltfPath)->second;};
    ImageDescription const &getImageDescription(std::string const &imageName) {return imageData.find(imageName)->second;};

protected:
    fs::path const rootDir = fs::current_path();
    fs::path const assetsDir = fs::current_path().append("assets");
    std::map<fs::path, std::string> fontsFileMap, imagesFileMap, shadersFileMap;
    std::map<std::string, std::string> tinyObjFileMap;
    std::map<std::string, std::vector<uint32_t>> spirVModules;
    std::map<std::string, std::string> gltfFileMap;
    std::map<std::string, ImageDescription> imageData;

private:
    AssetsManager();

    std::string assetType = type(this);
    std::vector<std::string> imageTypes = {".jpg", ".png", ".bmp", ".jpeg"};
    std::shared_ptr<spdlog::logger> assetsLogger = Zero::createSpdLogger(assetType, spdlog::level::debug);

    EShLanguage getShaderStage(std::string const &stage);
    void compileGLSL(fs::path const& file, std::string const& fileString);
    void recursivelyAcquire(fs::path const& path);
    void compileShaders();
    void setImageData();
};

}

#endif
