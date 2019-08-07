add_library(assets_manager assets_manager.cpp assets_manager.hpp)
#shaderc_default_compile_options(assets_manager)
target_include_directories(assets_manager PRIVATE ${shaderc_INCLUDE_DIRS})
target_link_libraries(assets_manager PRIVATE lib_shaderc stdc++fs utils)
