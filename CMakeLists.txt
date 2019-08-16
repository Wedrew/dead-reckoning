cmake_minimum_required(VERSION 3.11)

set(CMAKE_BUILD_TYPE "Debug")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- Building with Debug on")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("-- Building with Release on")
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Submodule settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the GLFW as shared library")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "Enable C++ 17")
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "Skip building SPIR-V header examples")
set(SKIP_SPIRV_TOOLS_INSTALL ON CACHE BOOL "Skip building SPIR-V tools")
set(SPIRV_SKIP_TESTS ON CACHE BOOL "Skip building SPIR-V tests")
set(SKIP_GLSLANG_INSTALL OFF CACHE BOOL "Skip glsland install")
set(SHADERC_ENABLE_SPVC OFF CACHE BOOL "Build SPVC command line wrapper")
set(JSON_BuildTests OFF CACHE BOOL "Build third party library tests")
set(JSON_Install OFF CACHE BOOL "Install library")

project(zero)

find_package(Vulkan REQUIRED FATAL_ERROR)

# TODO: Rework this to do target level includes
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# Configure external libraries
add_subdirectory(third_party)

# Add all the newely synced cmake projects
add_subdirectory(third_party/shaderc/src)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/spdlog)
add_subdirectory(third_party/json)
add_subdirectory(third_party/cxxopts)


# Add Modules
add_subdirectory(game)
add_subdirectory(window)
add_subdirectory(renderer)
add_subdirectory(character)
add_subdirectory(assets_manager)
add_subdirectory(texture_manager)
add_subdirectory(verlet_engine)
add_subdirectory(utils)

# Create game executable
add_executable(zero main.cpp)

# Link internal libraries
target_link_libraries(zero PUBLIC game spdlog utils)

# Link external libraries
target_link_libraries(zero PRIVATE nlohmann_json::nlohmann_json cxxopts)

# Move assets and shaders folders to build
file(COPY assets shaders DESTINATION ${CMAKE_BINARY_DIR})
