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

#include "game/game.hpp"
#include "utils/utils.hpp"
#include "json11.hpp"
#include "cxxopts.hpp"

#ifdef NDEBUG
    const bool Zero::Renderer::enableValidationLayers = false;
#else
    const bool Zero::Renderer::enableValidationLayers = true;
#endif

const std::string gameName = "Zero";

int main(int argc, char* argv[]) {
    auto mainLogger = Zero::createSpdLogger("main", spdlog::level::debug);;

    mainLogger->debug("Creating {} object", gameName);
    auto game = Zero::Game(gameName, 0);

    mainLogger->debug("Exiting from main");
    return 0;
}
