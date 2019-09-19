#include <stdexcept>
#include <string>
#include <chrono>

#include "window_manager/window_manager.hpp"

namespace Zero {

WindowManager::WindowManager(std::string title, int flags) : Renderer(title) {
    windowLogger->debug("Created Window object");

    initGLFW();
    initControllers();
    initWindow();
    initVulkan(window);
}

WindowManager::~WindowManager() {
    uninitializeRenderer(window);
    windowLogger->debug("Deleted Window object");
}

void WindowManager::initGLFW() {
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

void WindowManager::initWindow() {
    getMonitors();

    auto width = currentMonitor->modes.back()->width;
    auto height = currentMonitor->modes.back()->height;

    //window = glfwCreateWindow(width, height, title.c_str(), currentMonitor->monitor, window);
    window = glfwCreateWindow(640, 480, title.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetJoystickCallback(joyStickCallback);

    if(not window) {
        windowLogger->error("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window!");
    }
}

void WindowManager::mainLoop() {
    while(not glfwWindowShouldClose(window)) {
        //calculateFPS();
        glfwPollEvents();
        pollControllerInput();
        drawFrame();
    }
    waitDeviceIdle();
}

void WindowManager::initControllers() {
    if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
        int count;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
        windowLogger->debug("Axes available: {}", count);
    }
}

void WindowManager::pollControllerInput() {
    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
        if (state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS) {
            windowLogger->debug("Pressed A");
            // if(keyPresses.count(GLFW_GAMEPAD_BUTTON_A)) {
            //     if(keyPresses.find(GLFW_GAMEPAD_BUTTON_A)->second.pressHistory.back() == false) {
            //         windowLogger->debug("Pressed A");
            //         keyPresses.find(GLFW_GAMEPAD_BUTTON_A)->second.previous = true;
            //     }
            // } else {
            //     windowLogger->debug("Pressed A");
            //     std::vector<bool> presses = {true};
            //     keyPresses.insert(std::pair<int, KeyPress>(GLFW_GAMEPAD_BUTTON_A, presses));
            // }
        }
            //input_speed(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
    }
}

void WindowManager::calculateFPS() {
    static auto startTime = std::chrono::high_resolution_clock::now();
    static int frameCount = 0;

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
    frameCount++;

    // Only show fps every second
    if(time >= 1.0){
        windowLogger->debug("Current FPS: {}", frameCount);
        frameCount = 0;
        startTime = currentTime;
    }
}

void WindowManager::getMonitors() {
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

void WindowManager::keyCallback(GLFWwindow *_window, int key, int scancode, int action, int mods) {
    void *data = glfwGetWindowUserPointer(_window);
    auto window = static_cast<Zero::WindowManager *>(data);
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)
        glfwSetWindowShouldClose(window->window, GLFW_TRUE);
    if (key == GLFW_KEY_E and action == GLFW_PRESS)
        window->windowLogger->debug("Pressed E");
}

void WindowManager::joyStickCallback(int jid, int event) {
    static std::shared_ptr<spdlog::logger> windowLogger = Zero::createSpdLogger("Zero::WindowManager*", spdlog::level::debug);
    if (event == GLFW_CONNECTED) {
        const char *name = glfwGetJoystickName(jid);
        windowLogger->debug("Detected {} joystick connection", name);
    }
    else if (event == GLFW_DISCONNECTED) {
        windowLogger->debug("Detected {} joystick disconnection", jid);
    }
}

}