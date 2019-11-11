add_library(utils STATIC 
	source/utils.cpp 
	include/utils.hpp)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(utils PRIVATE configure)
target_link_libraries(utils PUBLIC spdlog::spdlog)
