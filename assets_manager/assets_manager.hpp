#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <string>
#include <filesystem>
#include <map>
#include <vector>

#include "utils/utils.hpp"
#include "shaderc/shaderc.hpp"

using fileMap = std::map<std::string, std::filesystem::path>;

namespace zero {

class AssetsManager {
public:
    AssetsManager(std::string dir);
    ~AssetsManager() = default;

    std::string getAsset(std::string name) const {return assetsCorrelation.at(name);};
    void refreshFiles();

    // Back class with iteration directorly for range based for loops
    fileMap::iterator begin() {return assetsCorrelation.begin();};
    fileMap::iterator end() {return assetsCorrelation.end();};
    fileMap &getAssets() {return assetsCorrelation;};

protected:
    std::filesystem::path const rootDir = std::filesystem::current_path();
    std::filesystem::path const assetsDir;
    std::vector<std::filesystem::path> assets;
    std::map<std::string, std::filesystem::path> assetsCorrelation;

private:
    std::string assetType = type(this);
    std::shared_ptr<spdlog::logger> assetsLogger = zero::createSpdLogger(assetType, spdlog::level::debug);
    void recursivelyAcquire(std::filesystem::path const& path);
    void correlate();
};
}

#endif
