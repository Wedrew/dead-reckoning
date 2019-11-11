//!**********************************************************
//! @file   main.cpp
//!
//! @author Andrew Pagan <apagan289@gmail.com>
//!
//! @date   June 2019
//!
//! @brief  Main entry point for Zero object. Creates singleton
//!         spdlog object and starts all of the game processing
//!         loops.
//!
//! Copyright 2019-2020 Harmonics Inc
//! All rights reserved.
//!***********************************************************/

#include "cxxopts.hpp"
#include "nlohmann/json.hpp"

#include "game.hpp"
#include "utils.hpp"
#include "config.hpp"

int main(int argc, char* argv[]) {
    auto mainLogger = Zero::createSpdLogger("main", spdlog::level::debug);

    mainLogger->debug("Creating game object");
    auto game = Zero::Game(0);

    return 0;
}
