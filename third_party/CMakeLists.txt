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

message(STATUS "GLFW was downloaded and configured")
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

message(STATUS "spdlog was downloaded and configured")
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


# ------------------------------------------------------------------------------
# json11 is a tiny JSON library for C++11, providing JSON parsing and
# serialization.
FetchContent_Declare(json11
    GIT_REPOSITORY https://github.com/dropbox/json11
    GIT_TAG master
    GIT_PROGRESS true
)

FetchContent_GetProperties(json11)

if(NOT json11_POPULATED)
    FetchContent_Populate(json11)
    set(JSON11_BUILD_TESTS OFF CACHE BOOL "")
    set(JSON11_ENABLE_DR1467_CANARY OFF CACHE BOOL "")

    add_subdirectory(${json11_SOURCE_DIR} ${json11_BINARY_DIR})
endif()

message(STATUS "json11 was downloaded and configured")
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

message(STATUS "cxxopts was downloaded and configured")
# -------------------------------------------------------------------------------

FetchContent_MakeAvailable(glfw spdlog glm json11 cxxopts)
