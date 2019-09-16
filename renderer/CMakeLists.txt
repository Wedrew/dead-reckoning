add_library(renderer STATIC renderer.cpp renderer.hpp renderer_helper.hpp)
target_link_libraries(renderer PRIVATE Vulkan::Vulkan glfw glm utils)
