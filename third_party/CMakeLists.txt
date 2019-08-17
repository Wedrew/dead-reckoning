find_package(Git QUIET)
find_package(Python3 COMPONENTS Interpreter)

# Submodule settings
set(BUILD_STATIC_LIBS ON CACHE BOOL "Build static libraries")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Dont build shared libraries")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "Enable C++ 17")
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "Skip building SPIR-V header examples")
set(SKIP_SPIRV_TOOLS_INSTALL ON CACHE BOOL "Skip building SPIR-V tools")
set(SPIRV_SKIP_TESTS ON CACHE BOOL "Skip building SPIR-V tests")
set(SKIP_GLSLANG_INSTALL ON CACHE BOOL "Skip glsland install")
set(SHADERC_ENABLE_SPVC OFF CACHE BOOL "Build SPVC command line wrapper")
set(SHADERC_SKIP_TESTS ON CACHE BOOL "Disable shaderc tests")
set(JSON_BuildTests OFF CACHE BOOL "Build third party library tests")
set(JSON_Install OFF CACHE BOOL "Install library")

# Update all the third party submodules
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    message(STATUS "Recursively updating git submodules")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --remote --init --recursive
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_INIT_RESULT
                    OUTPUT_QUIET)
    if(NOT GIT_SUBMOD_INIT_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_INIT_RESULT}, please checkout submodules")
    endif()

    message(STATUS "Updating shaderc git dependencies")
    execute_process(COMMAND ${Python3_EXECUTABLE} utils/git-sync-deps
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/shaderc
                    RESULT_VARIABLE GIT_SHADERC_DEPS_RESULT
                    OUTPUT_QUIET)
    if(NOT GIT_SHADERC_DEPS_RESULT EQUAL "0")
        message(FATAL_ERROR "Failed to update shaderc dependencies with error: ${GIT_SHADERC_DEPS_RESULT}")
    endif()


endif()
