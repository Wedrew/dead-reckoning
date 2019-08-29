add_library(assets_manager assets_manager.cpp assets_manager.hpp)
target_link_libraries(assets_manager stdc++fs glslang SPIRV glslang-default-resource-limits utils)