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
#include "window_manager/window_details.hpp"
#include "renderer.hpp"
#include "utils/utils.hpp"

using Callback = std::function<void()>;

namespace Zero {

struct KeyPress {
    std::vector<bool> pressHistory;
};

//Rename to window wrapper
class WindowManager : public Renderer {

public:
    WindowManager(std::string title, int flags);
    ~WindowManager();

protected:
    std::string title;

    void mainLoop();
    void initGLFW();
    void initWindow();
    void initControllers();
    void getMonitors();
    void pollControllerInput();
    void calculateFPS();
    static void keyCallback(GLFWwindow *_window, int key, int scancode, int action, int mods);
    static void joyStickCallback(int jid, int event);

private:
    uint32_t fps;
    std::string windowType = type(this);
    std::shared_ptr<spdlog::logger> windowLogger = Zero::createSpdLogger(windowType, spdlog::level::debug);
    std::map<int, KeyPress> keyPresses;
    std::vector<MonitorDetails> monitors;
    MonitorDetails *currentMonitor;
    GLFWwindow *window;
    GLFWgamepadstate state;

};
}


#endif