#include <stdexcept>
#include <string>
#include <chrono>

#include"window_manager.hpp"

namespace Zero {

WindowManager::WindowManager(int flags) : Renderer() {
    windowLogger->debug("Created Window object");

    initGLFW();
    initControllers();
    getMonitors();
    //createWindowIcon();
    initWindow();
    initVulkan(window);
}

WindowManager::~WindowManager() {
    uninitializeRenderer(window);
    windowLogger->debug("Deleted Window object");
}

void WindowManager::createWindowIcon() {
    auto image = assets->getImageDescription("running_1.png");

    icons[0].width = static_cast<int>(image.width);
    icons[0].height = static_cast<int>(image.height);
    icons[0].pixels = image.data;
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

    auto width = currentMonitor->modes.back()->width;
    auto height = currentMonitor->modes.back()->height;

    window = glfwCreateWindow(width, height, Zero::WINDOW_NAME.c_str(), glfwGetPrimaryMonitor(), nullptr);
    //window = glfwCreateWindow(640, 480, Zero::WINDOW_NAME.c_str(), nullptr, nullptr);

    if(not window) {
        windowLogger->error("Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetJoystickCallback(joyStickCallback);
    glfwSetWindowIcon(window, 1, icons);
    glfwSetCharCallback(window, characterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    if(glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        windowLogger->debug("Raw mouse motion enabled");
    }
}

void WindowManager::mainLoop() {
    while(not glfwWindowShouldClose(window)) {
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
    }
}

void WindowManager::pollControllerInput() {
    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
        if (state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS) {
            windowLogger->debug("Pressed A");
        }
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
    auto windowManager = static_cast<Zero::WindowManager *>(data);
    if(key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)
        glfwSetWindowShouldClose(windowManager->window, GLFW_TRUE);
    if(key == GLFW_KEY_E and action == GLFW_PRESS)
        windowManager->windowLogger->debug("Pressed E");
}

void WindowManager::joyStickCallback(int jid, int event) {
    static std::shared_ptr<spdlog::logger> windowLogger = Zero::createSpdLogger("Zero::WindowManager*", spdlog::level::debug);
    if(event == GLFW_CONNECTED) {
        const char *name = glfwGetJoystickName(jid);
        windowLogger->debug("Detected {} joystick connection", name);
    }
    else if(event == GLFW_DISCONNECTED) {
        windowLogger->debug("Detected {} joystick disconnection", jid);
    }
}

void WindowManager::frameBufferResizeCallback(GLFWwindow *window, int width, int height) {
    auto app = reinterpret_cast<Zero::WindowManager*>(glfwGetWindowUserPointer(window));
    app->setFrameBufferDimensions(width, height);
    app->setFrameBufferResize(true);
    app->windowLogger->debug("Resized window to {} by {}", width, height);
}

void WindowManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    auto app = reinterpret_cast<Zero::WindowManager*>(glfwGetWindowUserPointer(window));
    if(button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_PRESS) {
        app->windowLogger->debug("Right click registered");
    } else if(button == GLFW_MOUSE_BUTTON_LEFT) {
        if(action == GLFW_PRESS) {
            app->leftButtonDown = true;
        } else if(action == GLFW_RELEASE) {
            app->leftButtonDown = false;
        }
    }       
}

void WindowManager::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    auto app = reinterpret_cast<Zero::WindowManager*>(glfwGetWindowUserPointer(window));
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if(app->leftButtonDown and xPos >= 0 and xPos <= width and yPos >= 0 and yPos <= height) {
        app->windowLogger->debug("Left click registered. X,Y positions: {},{}", xPos, yPos);
    }

}

void WindowManager::characterCallback(GLFWwindow *window, unsigned int codepoint) {

}

void WindowManager::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    auto app = reinterpret_cast<Zero::WindowManager*>(glfwGetWindowUserPointer(window));
    if(app->distance == 1 and yOffset > 0) {
        app->windowLogger->warn("Minimum distance reached: {}", app->distance);
    } else if(app->distance > 0) {
        app->distance -= yOffset ;
        app->windowLogger->debug("New distance value: {}", app->distance);
    }
}

}