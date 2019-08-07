#include "assets_manager.hpp"

namespace zero {

AssetsManager::AssetsManager(std::string dirName) : assetsDir(std::filesystem::path(dirName)) {
    recursivelyAcquire(assetsDir);
    correlate();

    assetsLogger->info("Found directory {}", dirName);
}

void AssetsManager::recursivelyAcquire(std::filesystem::path const &path) {
    // Get all the files in the assets directory
    // TODO: more generic namespacing by folder name
    for(auto const &p: std::filesystem::recursive_directory_iterator(path)) {
        if(not p.is_directory()) {
            assets.push_back(p);
        }
    }
}

void AssetsManager::correlate() {
    // Correlate all the files names with the absolute paths
    for(auto const &p: assets) {
        assetsCorrelation.insert(std::pair<std::string, std::filesystem::path>(p.stem().string(), p));
    }
}

void AssetsManager::refreshFiles() {
    assets.clear();
    assetsCorrelation.clear();
    recursivelyAcquire(assetsDir);
    correlate();
}


}