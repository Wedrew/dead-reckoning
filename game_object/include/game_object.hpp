#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <memory>
#include <string>

#include "tiny_obj_loader.h"
#include "vulkan/vulkan.h"
#include "fx/gltf.h"

#include "mesh_manager.hpp"
#include "vertex.hpp"
#include "assets_manager.hpp"
#include "image_description.hpp"
#include "utils.hpp"

namespace Zero {
    
class GameObject {
public:
    GameObject(std::string gltfName);
    ~GameObject() = default;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    ImageDescription const &getImageDescription() {return assets->getImageDescription(modelName);};

protected:
    void loadModel();

private:
    std::string windowType = type(this);
    std::shared_ptr<AssetsManager> assets = AssetsManager::getAssetsManager();
    std::shared_ptr<spdlog::logger> gameObjectLogger = Zero::createSpdLogger(windowType, spdlog::level::debug);
    fx::gltf::Document gltfDocument;

    std::string modelName;
    std::string modelPath;

};

}

#endif