find_package(Python3 COMPONENTS Interpreter)

set(VK_LOADER_NAME Vulkan-Loader)
set(VK_LOADER_NUM_VERSION 1.1.121)
set(VK_LOADER_VERSION v${VK_LOADER_NUM_VERSION})
set(VK_LOADER_TAR_NAME ${VK_LOADER_NAME}-${VK_LOADER_VERSION}.tar.gz)
set(VK_LOADER_DOWNLOAD_PATH ${CMAKE_BINARY_DIR}/downloads)
set(VK_LOADER_URL https://github.com/KhronosGroup/Vulkan-Loader/archive/${VK_LOADER_VERSION}.tar.gz)
set(VK_LOADER_TARBAL_PATH ${CMAKE_BINARY_DIR}/downloads/${VK_LOADER_TAR_NAME})
set(VK_LOADER_EXTRACT_PATH ${CMAKE_BINARY_DIR}/downloads)

if(NOT EXISTS ${VK_LOADER_DOWNLOAD_PATH})
    file(MAKE_DIRECTORY ${VK_LOADER_DOWNLOAD_PATH})
endif()

if(NOT EXISTS ${VK_LOADER_DOWNLOAD_PATH}/${VK_LOADER_TAR_NAME})
    message(STATUS "Downloading vulkan loader tarball")
    file(DOWNLOAD ${VK_LOADER_URL} ${VK_LOADER_DOWNLOAD_PATH}/${VK_LOADER_TAR_NAME})
endif()

if(NOT EXISTS ${VK_LOADER_EXTRACT_PATH}/${VK_LOADER_NAME}-${VK_LOADER_NUM_VERSION})
    message(STATUS "Extracting vulkan loader tarball")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${VK_LOADER_TARBAL_PATH}
        WORKING_DIRECTORY ${VK_LOADER_EXTRACT_PATH}
        RESULT_VARIABLE VK_LOADER_EXTRACT_SUCCESS
        OUTPUT_QUIET)

    message(STATUS "Updating vulkan loader git dependencies")
    execute_process(COMMAND ${Python3_EXECUTABLE} scripts/update_deps.py
        WORKING_DIRECTORY ${VK_LOADER_EXTRACT_PATH}/${VK_LOADER_NAME}-${VK_LOADER_NUM_VERSION}
        RESULT_VARIABLE VK_LOADER_UPDATE_SUCCESS)

    if(VK_LOADER_UPDATE_SUCCESS EQUAL "1")
        message(FATAL_ERROR "Failed to update VK_LOADER dependencies")
    endif()

endif()

set(VK_LOADER_PATH ${CMAKE_BINARY_DIR}/downloads/${VK_LOADER_NAME}-${VK_LOADER_NUM_VERSION})
set(VULKAN_LOADER_INSTALL_DIR ${CMAKE_BINARY_DIR}/downloads/${VK_LOADER_NAME}-${VK_LOADER_NUM_VERSION} CACHE STRING "Tell vulkan validation layer where loader is")
set(VULKAN_HEADERS_INSTALL_DIR ${VK_LOADER_PATH}/Vulkan-Headers/build/install)
