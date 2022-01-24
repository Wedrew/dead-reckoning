cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(zeroth_order VERSION 0.1 LANGUAGES CXX C)

# Set required variables
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Find necessary vulkan packages
find_package(Vulkan REQUIRED FATAL_ERROR)

# Configure glslang and vulkan headers
include(third_party/cmake/glslang.cmake)
include(third_party/cmake/vulkan_headers.cmake)

# Add external cmake modules
add_subdirectory(${GLSLANG_PATH})
add_subdirectory(${VK_HEADER_PATH})

# Configure external libraries
add_subdirectory(third_party)

# Add internal cmake modules
add_subdirectory(configure)
add_subdirectory(game)
add_subdirectory(window_manager)
add_subdirectory(renderer)
add_subdirectory(utils)
add_subdirectory(assets_manager)
add_subdirectory(game_object)
add_subdirectory(controller)
#add_subdirectory(texture_manager)
#add_subdirectory(verlet_engine)

# Create game executable
add_executable(zeroth_order main.cpp)

#  Make binary static and link internal libraries
target_link_libraries(zeroth_order PUBLIC game configure)

# Link external libraries
target_link_libraries(zeroth_order PRIVATE cxxopts nlohmann_json::nlohmann_json)
