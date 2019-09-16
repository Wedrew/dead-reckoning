#ifndef WINDOW_DETAILS_H
#define WINDOW_DETAILS_H

#include <vector>
#include <string>

#define VULKAN_ENABLE_LUNARG_VALIDATION
#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"

// No need to deallocate this or use smart pointer, handled by glfw
struct MonitorDetails {
    GLFWmonitor *monitor;
    std::vector<GLFWvidmode const*> modes;
    uint8_t currentMode;
    std::string monitorName;
};

#endif