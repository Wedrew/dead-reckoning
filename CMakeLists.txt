cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(CMAKE_BUILD_TYPE "Release")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- Building with Debug on")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("-- Building with Release on")
ENDIF()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")
set(CMAKE_CXX_STANDARD 17 CACHE BOOL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(BUILD_STATIC_LIBS ON CACHE BOOL "")

project(zero VERSION 1.0 LANGUAGES CXX)

# TODO: Rework this to do target level includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Vulkan REQUIRED FATAL_ERROR)

# Configure glslang
include(cmake/glslang.cmake)

# Configure external libraries
add_subdirectory(third_party)

# Add external cmake modules
add_subdirectory(${CMAKE_BINARY_DIR}/glslang-7.12.3352)

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
add_executable(zero main.cpp)

# Link internal libraries
target_link_libraries(zero PUBLIC game utils)

# Link external libraries
target_link_libraries(zero PRIVATE nlohmann_json::nlohmann_json cxxopts)

# Move assets folder to build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
