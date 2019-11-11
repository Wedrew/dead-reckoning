add_library(game_object STATIC 
	source/game_object.cpp 
	include/game_object.hpp
	include/vertex.hpp
	include/mesh_manager.hpp)

target_include_directories(game_object PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(game_object PUBLIC fx-gltf tinyobjloader)
target_link_libraries(game_object PRIVATE Vulkan::Headers glm assets_manager utils)