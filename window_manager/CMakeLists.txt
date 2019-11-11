add_library(window_manager STATIC 
	source/window_manager.cpp 
	include/window_manager.hpp 
	include/window_details.hpp)

target_include_directories(window_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(window_manager PUBLIC renderer)