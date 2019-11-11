#define TINYOBJLOADER_IMPLEMENTATION

#include "game_object.hpp"

#include <unordered_map>

namespace Zero {

GameObject::GameObject(std::string modelName) : modelName(modelName), modelPath(assets->getTinyObjPath(modelName)) {
    loadModel();
    //createMesh(vertices, indices);
}


void GameObject::loadModel() {
	gltfDocument = fx::gltf::LoadFromBinary(assets->getGltfDocumentPath("engine"));
	gameObjectLogger->debug("Loaded gltf document: {}", "engine.glb");

	tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if(not tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
        gameObjectLogger->error("Failed to load object: {}", modelPath);
        gameObjectLogger->error("{} + {}", warn, err);
        throw std::runtime_error(warn + err);
    } else {
        gameObjectLogger->debug("Loaded object: {}", modelPath);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex = {};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = {1.0f, 1.0f, 1.0f};

            if(uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);
            }

            indices.push_back(uniqueVertices[vertex]);
        }
    }
}

}