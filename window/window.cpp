#include <stdexcept>
#include <string>

#include "window.hpp"

namespace zero {

Window::Window(std::string title, int flags) : Renderer(title) {
    windowLogger->debug("Created Window object");

    initGLFW();
    initWindow();
    initVulkan(window);
}

Window::~Window() {
    uninitializeRenderer(window);
    windowLogger->debug("Deleted Window object");
}

void Window::initGLFW() {
    // Add fail checks here, flags to the parameter, and the callback
    //glfwSetErrorCallback();
    //glfwSetMonitorCallback(monitor_callback);

    if(not glfwInit()) {
        windowLogger->error("Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW!");
    }
    if(not glfwVulkanSupported()) {
        windowLogger->debug("Vulkan is not supported. Defaulting to OpenGL backend");
    }
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Window::initWindow() {
    getMonitors();

    auto width = currentMonitor->modes.back()->width;
    auto height = currentMonitor->modes.back()->height;

    //window = glfwCreateWindow(width, height, title.c_str(), currentMonitor->monitor, window);
    window = glfwCreateWindow(640, 480, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

    if(not window) {
        windowLogger->error("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window!");
    }
}

void Window::mainLoop() {
    while(not glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame();
    }
    waitDeviceIdle();
}

void Window::getMonitors() {
    int numberOfMonitors = 0;
    GLFWmonitor **tempMonitors;
    tempMonitors = glfwGetMonitors(&numberOfMonitors);
    for(auto i = 0; i < numberOfMonitors; ++i) {
        int numOfVideoModes;
        GLFWvidmode const *modes = glfwGetVideoModes(tempMonitors[i], &numOfVideoModes);
        MonitorDetails monitor = MonitorDetails();

        monitor.monitor = tempMonitors[i];

        for(auto j = 0; j < numOfVideoModes; ++j) {
            monitor.modes.push_back(&modes[j]);
        }

        monitor.monitorName = glfwGetMonitorName(tempMonitors[i]);
        monitors.push_back(monitor);
    }

    for(auto const& monitor : monitors) {
        for(auto i = 0; i < monitor.modes.size(); ++i) {
            windowLogger->info("Monitor: {}, width={} height={} refresh rate={}", monitor.monitorName, monitor.modes.at(i)->width, monitor.modes.at(i)->height, monitor.modes.at(i)->refreshRate);
        }
    }
    currentMonitor = &monitors.front();
    currentMonitor->currentMode = currentMonitor->modes.size() - 1;
    setMonitor(currentMonitor);
}

}