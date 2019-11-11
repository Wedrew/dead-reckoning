#ifndef MESH_HPP
#define MESH_HPP

#include <array>
#include <vector>
#include <map>

#include "vulkan/vulkan.h"
#include "vertex.hpp"

namespace Zero {

struct Mesh {
    VkBuffer vBuffer;
    VkDeviceMemory vBufferMemory;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    int vertCount;
    int indexCount;
};

class MeshManager {
private:
    std::map<int, Mesh> meshes;

public:
    Mesh *getMeshData(int meshHdl) {return &meshes[meshHdl];};
};

}

#endif