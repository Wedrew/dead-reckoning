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

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

#include "window_manager.hpp"

namespace Zero {

class Game final : public WindowManager {
public:
    Game(int flags);
    ~Game();

    void updateEvents();
    void update();
    void render();
    void run();

    bool isRunning = true;
    int numDisplays;

private:
    std::string gameType = type(this);
    std::shared_ptr<spdlog::logger> gameLogger = Zero::createSpdLogger(gameType, spdlog::level::debug);
};
}

#endif
