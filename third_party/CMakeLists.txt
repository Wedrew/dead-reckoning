find_package(Git QUIET)
find_package(Python3 COMPONENTS Interpreter)

#set(SPIRV_CROSS_PATH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-tools")
#set(CHECKOUT_SPIRV_TOOLS_SH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-cross/build_glslang_spirv_tools.sh")
#set(BUILD_SPIRV_TOOLS_SH "${CMAKE_SOURCE_DIR}/third_party/shaderc/third_party/spirv-cross/checkout_glslang_spirv_tools.sh")


# Update all the third party submodules
if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    message(STATUS "Recursively updating git submodules")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT
                    OUTPUT_QUIET)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()

    # Sync shaderc git dependencies
    #execute_process(COMMAND ${CHECKOUT_SPIRV_TOOLS_SH}
                    #WORKING_DIRECTORY ${SPIRV_CROSS_PATH})

    #execute_process(COMMAND ${BUILD_SPIRV_TOOLS_SH}
                    #WORKING_DIRECTORY ${SPIRV_CROSS_PATH})

    message(STATUS "Updating shaderc sources")
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/third_party/shaderc/update_shaderc_sources.py 
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/shaderc
                    OUTPUT_QUIET)

    message(STATUS "Updating shaderc git dependencies")
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/third_party/shaderc/src/utils/git-sync-deps
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/shaderc/src/utils
                    OUTPUT_QUIET)


endif()
