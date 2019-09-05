add_library(utils STATIC utils.cpp utils.hpp)
target_link_libraries(utils spdlog::spdlog)
