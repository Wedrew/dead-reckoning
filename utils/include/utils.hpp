#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <typeinfo>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Zero {

std::string demangle(char const* name);

template <class T>
std::string type(const T& t) {
    return demangle(typeid(t).name());
}

std::shared_ptr<spdlog::logger> createSpdLogger(std::string subsystemName, spdlog::level::level_enum level);

}

#endif