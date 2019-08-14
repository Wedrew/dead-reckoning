#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <string>
#include <filesystem>
#include <map>
#include <vector>

#include "utils/utils.hpp"
#include "shaderc/shaderc.hpp"

namespace fs = std::filesystem;
using FileMap = std::map<fs::path, std::string>;

namespace zero {

class AssetsManager {
public:
    AssetsManager(std::string dir);
    ~AssetsManager() = default;

    std::string getAsset(std::string name) const {return assets.at(name);};
    bool compileShaders(bool optimize);
    void refreshFiles();

    // Back class with iteration directorly for range based for loops
    FileMap::iterator begin() {return assets.begin();};
    FileMap::iterator end() {return assets.end();};
    FileMap const &getAssets() {return assets;};

protected:
    fs::path const rootDir = fs::current_path();
    fs::path const assetsDir;
    std::map<fs::path, std::string> assets;
    std::map<fs::path, std::vector<uint32_t>> spirVModules;

private:
    std::string assetType = type(this);
    std::shared_ptr<spdlog::logger> assetsLogger = zero::createSpdLogger(assetType, spdlog::level::debug);
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    std::string preprocessShader(fs::path const &path, shaderc_shader_kind kind, std::string const &source);
    std::string compileToAssembly(fs::path const &path, shaderc_shader_kind kind, std::string const &source, bool optimize = false);
    std::vector<uint32_t> compileFile(fs::path const &path, shaderc_shader_kind kind, std::string const &source, bool optimize = false);
    void recursivelyAcquire(fs::path const& path);
};
}

#endif
