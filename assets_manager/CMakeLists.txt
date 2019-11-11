add_library(assets_manager STATIC 
	source/assets_manager.cpp 
	include/assets_manager.hpp
	include/image_description.hpp
	../third_party/stb/stb_image.h)

target_include_directories(assets_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(assets_manager PUBLIC ${CMAKE_SOURCE_DIR}/third_party/stb)
target_include_directories(assets_manager PUBLIC ${GLSLANG_PATH})

target_link_libraries(assets_manager PUBLIC fx-gltf nlohmann_json::nlohmann_json)
target_link_libraries(assets_manager PRIVATE stdc++fs glslang SPIRV SPVRemapper glslang-default-resource-limits utils)