add_library(game STATIC game.cpp game.hpp)
target_link_libraries(game PUBLIC window_manager)