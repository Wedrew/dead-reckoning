find_package(Git QUIET)
find_package(Python3 COMPONENTS Interpreter)

#set(SPIRV_CROSS_PATH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-tools")
#set(CHECKOUT_SPIRV_TOOLS_SH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-cross/build_glslang_spirv_tools.sh")
#set(BUILD_SPIRV_TOOLS_SH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-cross/checkout_glslang_spirv_tools.sh")

# Submodule settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the GLFW as shared library")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "Enable C++ 17")
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "Skip building SPIR-V header examples")
#set(SHADERC_ENABLE_SPVC ON CACHE BOOL "Build SPVC command line wrapper")
set(JSON_BuildTests OFF CACHE BOOL "Build third party library tests")
set(JSON_Install OFF CACHE BOOL "Install library")

# Update all the third party submodules
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()

    # Sync shaderc git dependencies
    #execute_process(COMMAND ${CHECKOUT_SPIRV_TOOLS_SH}
                    #WORKING_DIRECTORY ${SPIRV_CROSS_PATH})

    #execute_process(COMMAND ${BUILD_SPIRV_TOOLS_SH}
                    #WORKING_DIRECTORY ${SPIRV_CROSS_PATH})

    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/third_party/shaderc/update_shaderc_sources.py 
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/shaderc)

endif()
