#ifndef WINDOW_H
#define WINDOW_H

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

#include <vector>
#include <string>

#define VULKAN_ENABLE_LUNARG_VALIDATION
#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "utils/utils.hpp"
#include "renderer/renderer.hpp"
#include "assets_manager/assets_manager.hpp"
#include "window/window_details.hpp"

namespace zero {

class Window : public Renderer {

public:
    Window(std::string title, int flags);
    ~Window();

protected:
    std::string title;

    void mainLoop();
    void initGLFW();
    void initWindow();
    void getMonitors();

private:
    std::string windowType = type(this);
    std::shared_ptr<spdlog::logger> windowLogger = zero::createSpdLogger(windowType, spdlog::level::debug);
    AssetsManager assets = AssetsManager("assets/images");
    std::vector<MonitorDetails> monitors;
    MonitorDetails *currentMonitor;
    GLFWwindow *window;

};
}


#endif