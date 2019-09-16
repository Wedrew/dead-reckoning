add_library(assets_manager STATIC assets_manager.cpp assets_manager.hpp)
target_link_libraries(assets_manager PRIVATE stdc++fs glslang SPIRV glslang-default-resource-limits utils)