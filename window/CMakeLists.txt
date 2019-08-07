add_library(window window.cpp window.hpp)
target_include_directories(window PRIVATE ${glfw_SOURCE_DIR}/include)
target_link_libraries(window PRIVATE glfw renderer utils assets_manager)