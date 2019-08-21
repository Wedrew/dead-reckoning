cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

set(CMAKE_BUILD_TYPE "Debug")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("-- Building with Debug on")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
  message("-- Building with Release on")
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(zero)

find_package(Vulkan REQUIRED FATAL_ERROR)

# TODO: Rework this to do target level includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Configure shaderc
include(cmake/shaderc.cmake)

# Configure external libraries
add_subdirectory(third_party)

# Add Modules
add_subdirectory(${CMAKE_BINARY_DIR}/shaderc-2019.0)
include_directories(${glfw_SOURCE_DIR}/include)
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
