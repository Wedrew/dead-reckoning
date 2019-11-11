include(FetchContent)

# # -----------------------------------------------------------------------------
# # Meta loader for Vulkan API
# FetchContent_Declare(volk
#     GIT_REPOSITORY https://github.com/zeux/volk.git
#     GIT_TAG master
#     GIT_PROGRESS true
# )

# FetchContent_GetProperties(volk)

# if(NOT volk_POPULATED)
#     FetchContent_Populate(volk)

#     add_subdirectory(${volk_SOURCE_DIR} ${volk_BINARY_DIR})
# endif()

# message(STATUS "Volk was downloaded and configured")
# # -----------------------------------------------------------------------------


# -------------------------------------------------------------------------------
# A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and
# input http://www.glfw.org/
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3
    GIT_PROGRESS true
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    set(GLFW_VULKAN_STATIC ON CACHE BOOL "")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

message(STATUS "GLFW was downloaded and configured")
# ------------------------------------------------------------------------------


# # -----------------------------------------------------------------------------
# # A library to import and export various 3d-model-formats including 
# # scene-post-processing to generate missing render data.
# FetchContent_Declare(assimp
#     GIT_REPOSITORY https://github.com/assimp/assimp.git
#     GIT_TAG v5.0.0
#     GIT_PROGRESS true
# )

# FetchContent_GetProperties(assimp)

# if(NOT assimp_POPULATED)
#     FetchContent_Populate(assimp)
#     set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
#     set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "")
#     set(ASSIMP_OPT_BUILD_PACKAGES ON CACHE BOOL "")
    
#     add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
# endif()

# message(STATUS "assimp was downloaded and configured")
# # -----------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# A header only fast logging library
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.4.1
    GIT_PROGRESS true
)

FetchContent_GetProperties(spdlog)

if(NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "")
    set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "")

    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

message(STATUS "spdlog was downloaded and configured")
# -------------------------------------------------------------------------------


# -------------------------------------------------------------------------------
# JSON for Modern C++ https://nlohmann.github.io/json/
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.7.0
    GIT_PROGRESS true
)

FetchContent_GetProperties(json)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    set(JSON_BuildTests OFF CACHE BOOL "")
    set(JSON_Install ON CACHE BOOL "")

    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

message(STATUS "nlohmannjson was downloaded and configured")
# -------------------------------------------------------------------------------


# -------------------------------------------------------------------------------
# A C++14/C++17 header-only library for simple, efficient, and robust 
# serialization/deserialization of glTF 2.0
FetchContent_Declare(fx-gltf
    GIT_REPOSITORY https://github.com/jessey-git/fx-gltf.git
    GIT_TAG v1.1.0
    GIT_PROGRESS true
)

FetchContent_GetProperties(fx-gltf)

if(NOT fx-gltf_POPULATED)
    FetchContent_Populate(fx-gltf)
    set(FX_GLTF_INSTALL OFF CACHE BOOL "")
    set(BUILD_TEST OFF CACHE BOOL "")

    add_subdirectory(${fx-gltf_SOURCE_DIR} ${fx-gltf_BINARY_DIR})
endif()

message(STATUS "fx-gltf was downloaded and configured")
# -------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics 
# software
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.5
    GIT_PROGRESS true
)

FetchContent_GetProperties(glm)

if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    set(GLM_TEST_ENABLE OFF CACHE BOOL "")
    set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "")
    set(GLM_INSTALL_ENABLE OFF CACHE BOOL "")
    set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "")
    set(GLM_QUIET ON CACHE BOOL "")

    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

message(STATUS "GLM was downloaded and configured")
# -------------------------------------------------------------------------------


# -------------------------------------------------------------------------------
# A lightweight C++ option parser library, supporting the standard GNU style syntax 
# for options.
FetchContent_Declare(cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v2.2.0
    GIT_PROGRESS true
)

FetchContent_GetProperties(cxxopts)

if(NOT cxxopts_POPULATED)
    FetchContent_Populate(cxxopts)
    set(CXXOPTS_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(CXXOPTS_BUILD_TESTS OFF CACHE BOOL "")
    set(CXXOPTS_ENABLE_INSTALL OFF CACHE BOOL "")

    add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BINARY_DIR})
endif()

message(STATUS "cxxopts was downloaded and configured")
# -------------------------------------------------------------------------------


# -------------------------------------------------------------------------------
# Tiny but powerful single file wavefront obj loader written in C++03. No 
# dependency except for C++ STL. It can parse over 10M polygons with moderate 
# memory and time.
FetchContent_Declare(tinyobjloader
    GIT_REPOSITORY https://github.com/syoyo/tinyobjloader
    GIT_TAG master
    GIT_PROGRESS true
)

FetchContent_GetProperties(tinyobjloader)

if(NOT tinyobjloader_POPULATED)
    FetchContent_Populate(tinyobjloader)

    add_subdirectory(${tinyobjloader_SOURCE_DIR} ${tinyobjloader_BINARY_DIR})
endif()

message(STATUS "tinyobjloader was downloaded and configured")
# ------------------------------------------------------------------------------
