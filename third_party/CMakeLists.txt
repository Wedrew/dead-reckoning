include(FetchContent)


# ------------------------------------------------------------------------------
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

message(STATUS "GLFW finished downloading")
# ------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# A header only fast logging library
FetchContent_Declare(spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.3.1
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

message(STATUS "spdlog finished downloading")
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
    set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "")

    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

message(STATUS "GLM finished downloading")
# -------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Modern json parser for c++ https://nlohmann.github.io/json/
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.6.1
    GIT_PROGRESS true
)

FetchContent_GetProperties(json)

if(NOT json_POPULATED)
    FetchContent_Populate(json)
    set(JSON_BuildTests OFF CACHE BOOL "")
    set(JSON_Install OFF CACHE BOOL "")

    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

message(STATUS "Nlohmann json finished downloading")
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

    add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BINARY_DIR})
endif()

message(STATUS "cxxopts finished downloading")
# -------------------------------------------------------------------------------

FetchContent_MakeAvailable(glfw spdlog glm json cxxopts)