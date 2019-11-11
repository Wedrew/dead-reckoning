//!**********************************************************
//! @file   window.cpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Defines everything specific to a Window in GLFW
//!         and inherits from a renderer, either OpenGL or
//!         Vulkan, depending on hardware support.
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <vector>
#include <string>
#include <memory>

#include "GLFW/glfw3.h"

#include "config.hpp"
#include "assets_manager.hpp"
#include "window_details.hpp"
#include "renderer.hpp"
#include "utils.hpp"

using Callback = std::function<void()>;

namespace Zero {

class WindowManager : public Renderer {

public:
    WindowManager(int flags);
    ~WindowManager();

protected:
    void mainLoop();
    void initGLFW();
    void initWindow();
    void initControllers();
    void getMonitors();
    void pollControllerInput();
    void createWindowIcon();
    void setFrameBufferResize(bool wasResized) {frameBufferResized = wasResized;};
    static void characterCallback(GLFWwindow *window, unsigned int codepoint);
    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
    static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow *_window, int key, int scancode, int action, int mods);
    static void joyStickCallback(int jid, int event);
    static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);

private:
    std::string windowType = type(this);
    std::shared_ptr<AssetsManager> assets = AssetsManager::getAssetsManager();
    std::shared_ptr<spdlog::logger> windowLogger = Zero::createSpdLogger(windowType, spdlog::level::debug);
    std::vector<MonitorDetails> monitors;
    MonitorDetails *currentMonitor;
    GLFWwindow *window;
    GLFWgamepadstate state;
    GLFWimage icons[1];

};
}


#endif