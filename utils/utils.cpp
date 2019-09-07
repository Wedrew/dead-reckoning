#include "utils.hpp"

namespace zero {

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(char const* name) {
    int status = -4;

    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name;
}

#else

std::string demangle(char const* name) {
    return name;
}

#endif

std::shared_ptr<spdlog::logger> createSpdLogger(std::string subsystemName, spdlog::level::level_enum level) {
    auto &sinks = spdlog::default_logger()->sinks();
    auto logger = std::make_shared<spdlog::logger>(subsystemName, sinks.begin(), sinks.end());
    logger->set_level(level);

    return logger;
}

std::shared_ptr<spdlog::sinks::stdout_color_sink_st> createSpdSink(std::string subsystemName, spdlog::level::level_enum level) {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    consoleSink->set_level(level);

    return consoleSink;
}

}
