#ifndef WINDOW_DETAILS_HPP
#define WINDOW_DETAILS_HPP

namespace Zero {

// No need to deallocate this or use smart pointer, handled by glfw
struct MonitorDetails {
    GLFWmonitor *monitor;
    std::vector<GLFWvidmode const*> modes;
    uint8_t currentMode;
    std::string monitorName;
};
}

#endif