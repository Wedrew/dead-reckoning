set(VK_HEADER_NAME Vulkan-Headers)
set(VK_HEADER_NUM_VERSION 1.1.123)
set(VK_HEADER_VERSION v${VK_HEADER_NUM_VERSION})
set(VK_HEADER_TAR_NAME ${VK_HEADER_NAME}-${VK_HEADER_VERSION}.tar.gz)
set(VK_HEADER_DOWNLOAD_PATH ${CMAKE_BINARY_DIR}/downloads)
set(VK_HEADER_URL https://github.com/KhronosGroup/Vulkan-Headers/archive/${VK_HEADER_VERSION}.tar.gz)
set(VK_HEADER_TARBAL_PATH ${CMAKE_BINARY_DIR}/downloads/${VK_HEADER_TAR_NAME})
set(VK_HEADER_EXTRACT_PATH ${CMAKE_BINARY_DIR}/downloads)

if(NOT EXISTS ${VK_HEADER_DOWNLOAD_PATH})
    file(MAKE_DIRECTORY ${VK_HEADER_DOWNLOAD_PATH})
endif()

if(NOT EXISTS ${VK_HEADER_DOWNLOAD_PATH}/${VK_HEADER_TAR_NAME})
    message(STATUS "Downloading vulkan header tarball")
    file(DOWNLOAD ${VK_HEADER_URL} ${VK_HEADER_DOWNLOAD_PATH}/${VK_HEADER_TAR_NAME})
endif()

if(NOT EXISTS ${VK_HEADER_EXTRACT_PATH}/${VK_HEADER_NAME}-${VK_HEADER_NUM_VERSION})
    message(STATUS "Extracting vulkan header tarball")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${VK_HEADER_TARBAL_PATH}
        WORKING_DIRECTORY ${VK_HEADER_EXTRACT_PATH}
        RESULT_VARIABLE VK_HEADER_EXTRACT_SUCCESS
        OUTPUT_QUIET)
endif()

set(VK_HEADER_PATH ${CMAKE_BINARY_DIR}/downloads/${VK_HEADER_NAME}-${VK_HEADER_NUM_VERSION})