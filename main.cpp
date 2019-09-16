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
//#include "nlohmann/json.hpp"
#include "cxxopts.hpp"

#ifdef NDEBUG
    const bool zero::Renderer::enableValidationLayers = false;
#else
    const bool zero::Renderer::enableValidationLayers = true;
#endif

const std::string gameName = "Zero";

int main(int argc, char* argv[]) {
    auto consoleSink = zero::createSpdSink(gameName, spdlog::level::debug);
    auto mainLogger = zero::createSpdLogger("main", spdlog::level::debug);;
    spdlog::register_logger(mainLogger);

    mainLogger->debug("Creating {} object", gameName);
    auto game = zero::Game(gameName, 0);

    mainLogger->debug("Exiting from main");
    return 0;
}
