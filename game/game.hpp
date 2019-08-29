//!**********************************************************
//! @file   game.cpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Defines all of the higher level game logic necessary
//!         to update the inherited window and renderer. This 
//!         class should be agnostic of renderer type.
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "window/window.hpp"
#include "utils/utils.hpp"

namespace zero {

class Game final : public Window {
public:
    Game(std::string title, uint flags);
    ~Game();

    void updateEvents();
    void update();
    void render();
    void run();

    bool isRunning = true;
    int numDisplays;

private:
    std::string gameType = type(this);
    std::shared_ptr<spdlog::logger> gameLogger = zero::createSpdLogger(gameType, spdlog::level::debug);
};
}

#endif
