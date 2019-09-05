add_library(window STATIC window.cpp window.hpp window_details.hpp)
target_link_libraries(window glfw utils renderer assets_manager)
