#include <optional>
#include "utils.hpp"
#include "config.hpp"

namespace Zero {

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
    //static auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Zero::LOG_FILE, "fileLogger");
    //static auto fileSink = spdlog::basic_logger_mt<spdlog::async_factory>("logs/log.txt", "file_logger");

    auto &sinks = spdlog::default_logger()->sinks();
    auto logger = std::make_shared<spdlog::logger>(subsystemName, sinks.begin(), sinks.end());
    logger->set_level(level);

    //auto logger = std::make_shared<spdlog::logger>(subsystemName, spdlog::sinks_init_list{consoleSink, fileSink});

    return logger;
}

// std::shared_ptr<spdlog::logger> createSpdLogger(std::string subsystemName, spdlog::level::level_enum level) {
//     static auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Zero::LOG_FILE, "fileLogger");
//     //static auto fileSink = spdlog::basic_logger_mt<spdlog::async_factory>("logs/log.txt", "file_logger");

//     auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
//     consoleSink->set_level(level);

//     spdlog::logger logger(subsystemName,  spdlog::sinks_init_list({consoleSink, fileSink}));

//     //auto logger = std::make_shared<spdlog::logger>(subsystemName, spdlog::sinks_init_list{consoleSink, fileSink});

//     return std::make_shared<spdlog::logger>(logger);
// }


}