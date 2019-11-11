add_library(controller STATIC 
	source/controller.cpp 
	include/controller.hpp )

target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(controller PUBLIC renderer)