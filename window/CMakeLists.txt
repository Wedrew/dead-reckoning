add_library(window window.cpp window.hpp)
target_link_libraries(window glfw utils renderer assets_manager)
