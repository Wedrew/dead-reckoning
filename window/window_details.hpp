#ifndef WINDOW_DETAILS_H
#define WINDOW_DETAILS_H

#include <vector>
#include <string>

#include "GLFW/glfw3.h"

// No need to deallocate this or use smart pointer, handled by glfw
struct MonitorDetails {
    GLFWmonitor *monitor;
    std::vector<GLFWvidmode const*> modes;
    std::string monitorName;
};

#endif