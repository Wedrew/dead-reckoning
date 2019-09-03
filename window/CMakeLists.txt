add_library(window window.cpp window.hpp window_details.hpp)
target_link_libraries(window glfw utils renderer assets_manager)
