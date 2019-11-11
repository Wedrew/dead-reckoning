add_library(renderer STATIC 
	source/renderer.cpp 
	include/renderer.hpp 
	include/debug_helper.hpp 
	include/queue_family_indices.hpp 
	include/swap_chain_support_details.hpp
	include/uniform_buffer.hpp)

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(renderer PUBLIC Vulkan::Vulkan Vulkan::Headers glfw glm window_manager assets_manager game_object configure utils)