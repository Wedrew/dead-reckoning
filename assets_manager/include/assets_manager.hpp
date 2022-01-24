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
using FileAndContents = std::pair<fs::path, std::string>;

namespace Zero {

class AssetsManager {

public:
    ~AssetsManager() = default;
    static std::shared_ptr<AssetsManager> getAssetsManager();

    void refreshFiles();
    std::string const getPath(std::string const &fileName) {return files.find(fileName)->second.first.string();};
    std::string const &getContent(std::string const &fileName) {return files.find(fileName)->second.second;};

    std::vector<uint32_t> const &getSpirvModules(std::string const &moduleName) {return spirVModules.find(moduleName)->second;};
    ImageDescription const &getImageDescription(std::string const &imageName) {return imageData.find(imageName)->second;};

protected:
    std::map<std::string, FileAndContents> files;

    fs::path const rootDir = fs::current_path();
    fs::path const assetsDir = fs::current_path().append("assets");
    std::map<std::string, std::vector<uint32_t>> spirVModules;
    std::map<std::string, ImageDescription> imageData;

private:
    AssetsManager();
    AssetsManager(const AssetsManager&) = delete;
    AssetsManager(AssetsManager&&) = delete;
    AssetsManager& operator=(const AssetsManager&) = delete;
    AssetsManager& operator=(AssetsManager&&) = delete;

    std::string assetType = type(this);
    std::vector<std::string> imageTypes = {".jpg", ".png", ".bmp", ".jpeg"};
    std::vector<std::string> shaderExtensions = {".vert", ".frag"};
    std::shared_ptr<spdlog::logger> assetsLogger = Zero::createSpdLogger(assetType, spdlog::level::debug);

    EShLanguage getShaderStage(std::string const &stage);
    void compileGLSL(fs::path const& file, std::string const& fileContents);
    void recursivelyAcquire(fs::path const& path);
    void compileShaders();
    void setImageData();
};

}

#endif
