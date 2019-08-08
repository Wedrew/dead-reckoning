add_library(assets_manager assets_manager.cpp assets_manager.hpp)
#shaderc_default_compile_options(assets_manager)
#target_include_directories(assets_manager PUBLIC ${shaderc_SOURCE_DIR}/libshaderc_utils/include)
target_link_libraries(assets_manager PRIVATE stdc++fs utils)
