#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <string>
#include <filesystem>
#include <map>
#include <vector>

#include "glslang/Public/ShaderLang.h"
#include "SPIRV/GlslangToSpv.h"
#include "utils/utils.hpp"

namespace fs = std::filesystem;
using FileMap = std::map<fs::path, std::string>;
using SpirVMap = std::map<std::string, std::vector<uint32_t>>;

namespace zero {

class AssetsManager {
public:
    AssetsManager();
    ~AssetsManager() = default;

    //std::string getAsset(std::string name) const {return assets.at(name);};
    void compileShaders(bool optimize);
    void refreshFiles();
    bool areShadersCompiled() {return shadersDone;};

    // Back class with iteration directorly for range based for loops
    SpirVMap::iterator begin() {return spirVModules.begin();};
    SpirVMap::iterator end() {return spirVModules.end();};
    std::vector<uint32_t> const &getSpirvModules(std::string moduleName) {return spirVModules.find(moduleName)->second;};
    //FileMap const &getAssets() {return assets;};

protected:
    bool shadersDone = false;
    fs::path const rootDir = fs::current_path();
    fs::path const assetsDir = fs::current_path().append("assets");
    std::map<fs::path, std::string> fontsFileMap, imagesFileMap, shadersFileMap;
    std::map<std::string, std::vector<uint32_t>> spirVModules;

private:
    std::string assetType = type(this);
    std::shared_ptr<spdlog::logger> assetsLogger = zero::createSpdLogger(assetType, spdlog::level::debug);

    EShLanguage getShaderStage(std::string const &stage);
    void compileGLSL(fs::path const& file, std::string const& fileString);
    void recursivelyAcquire(fs::path const& path);
};
}

#endif
