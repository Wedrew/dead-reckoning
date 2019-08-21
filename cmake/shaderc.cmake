find_package(Python3 COMPONENTS Interpreter)

# Submodule settings
set(SPIRV_HEADERS_SKIP_EXAMPLES ON CACHE BOOL "Skip building SPIR-V header examples")
set(SKIP_SPIRV_TOOLS_INSTALL ON CACHE BOOL "Skip building SPIR-V tools")
set(SPIRV_SKIP_TESTS ON CACHE BOOL "Skip building SPIR-V tests")
set(SKIP_GLSLANG_INSTALL OFF CACHE BOOL "Skip glsland install")
set(SHADERC_ENABLE_SPVC OFF CACHE BOOL "Build SPVC command line wrapper")

set(DOWNLOAD_PATH ${CMAKE_BINARY_DIR}/downloads)
set(SHADERC_URL https://github.com/google/shaderc/archive/v2019.0.tar.gz)
set(SHADERC_TARBAL ${CMAKE_BINARY_DIR}/downloads/shaderc-2019.0.tar.gz)
set(SHADERC_EXTRACT_PATH ${CMAKE_BINARY_DIR}/third_party)

if(NOT EXISTS ${DOWNLOAD_PATH})
    file(MAKE_DIRECTORY ${DOWNLOAD_PATH})

    message(STATUS "Downloading shaderc tarball")
    file(DOWNLOAD ${SHADERC_URL} ${SHADERC_TARBAL})

    message(STATUS "Exctracing shaderc tarball")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${SHADERC_TARBAL} OUTPUT_QUIET)

    message(STATUS "Updating shaderc git dependencies")
    execute_process(COMMAND ${Python3_EXECUTABLE} ${CMAKE_BINARY_DIR}/shaderc-2019.0/utils/git-sync-deps OUTPUT_QUIET)
endif()