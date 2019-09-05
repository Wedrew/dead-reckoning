cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(zeroth_order VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "")
set(BUILD_SHARED_LIBS ON CACHE BOOL "")

# TODO: Rework this to do target level includes
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# Configure glslang, vulkan
include(cmake/glslang.cmake)
include(cmake/vulkan_headers.cmake)
include(cmake/vulkan_loader.cmake)
include(cmake/vulkan_validation_layers.cmake)

# Add external cmake modules
add_subdirectory(${GLSLANG_PATH})
add_subdirectory(${VK_HEADER_PATH})
add_subdirectory(${VK_LOADER_PATH})
add_subdirectory(${VK_VALIDATION_PATH})

# Configure external libraries
add_subdirectory(third_party)

# Add internal cmake modules
add_subdirectory(game)
add_subdirectory(window)
add_subdirectory(renderer)
add_subdirectory(utils)
add_subdirectory(assets_manager)
#add_subdirectory(character)
#add_subdirectory(texture_manager)
#add_subdirectory(verlet_engine)

# Create game executable
add_executable(zeroth_order main.cpp)

# Link internal libraries
target_link_libraries(zeroth_order game utils)

# Link external libraries
target_link_libraries(zeroth_order nlohmann_json::nlohmann_json cxxopts)

# Move assets folder to build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
