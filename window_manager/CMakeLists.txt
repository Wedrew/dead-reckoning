add_library(window_manager STATIC window_manager.cpp window_manager.hpp)
target_link_libraries(window_manager PUBLIC renderer)
