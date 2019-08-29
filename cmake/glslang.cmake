find_package(Python3 COMPONENTS Interpreter)

#set(ENABLE_OPT)

set(DOWNLOAD_PATH ${CMAKE_BINARY_DIR}/downloads)
set(GLSLANG_URL https://github.com/KhronosGroup/glslang/archive/7.12.3352.tar.gz)
set(GLSLANG_TARBAL ${CMAKE_BINARY_DIR}/downloads/master-tot.tar.gz)
set(GLSLANG_EXTRACT_PATH ${CMAKE_BINARY_DIR}/third_party)

if(NOT EXISTS ${DOWNLOAD_PATH})
    file(MAKE_DIRECTORY ${DOWNLOAD_PATH})

    # Add check for if untared folder exists
    message(STATUS "Downloading glslang tarball")
    file(DOWNLOAD ${GLSLANG_URL} ${GLSLANG_TARBAL})

    message(STATUS "Exctracting glslang tarball")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${GLSLANG_TARBAL} OUTPUT_QUIET)

    message(STATUS "Updating glslang git dependencies")
    execute_process(COMMAND ${Python3_EXECUTABLE} update_glslang_sources.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/glslang-7.12.3352)
endif()