add_library(renderer renderer.cpp renderer.hpp renderer_helper.hpp)
target_include_directories(renderer PRIVATE ${glfw_SOURCE_DIR}/include)
target_link_libraries(renderer Vulkan::Vulkan glfw glm utils)