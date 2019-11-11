add_library(game STATIC 
	source/game.cpp 
	include/game.hpp)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(game PUBLIC window_manager)