#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <typeinfo>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zero {

std::string demangle(char const* name);

template <class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}

// Add ability set log level via parameter spdlog::level::level_enum
std::shared_ptr<spdlog::logger> createSpdLogger(std::string subsystemName, spdlog::level::level_enum level);

std::shared_ptr<spdlog::sinks::stdout_color_sink_st> createSpdSink(std::string subsystemName, spdlog::level::level_enum level);

}

#endif