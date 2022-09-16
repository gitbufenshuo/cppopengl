#ifndef MC_LOG_LOG_H
#define MC_LOG_LOG_H

#include <mc/config.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define SPD_INFO(...) mc::log::Log::GetLogger()->info(__VA_ARGS__)
#define SPD_WARN(...) mc::log::Log::GetLogger()->warn(__VA_ARGS__)
#define SPD_DEBUG(...) mc::log::Log::GetLogger()->debug(__VA_ARGS__)
#define SPD_TRACE(...) mc::log::Log::GetLogger()->trace(__VA_ARGS__)
#define SPD_ERROR(...) mc::log::Log::GetLogger()->error(__VA_ARGS__)

// exceptions, error handling and varying levels of logging is part of the app's normal workflow
// assertions however, must hold in any correct release build, they only apply to the debug mode

#if defined(_DEBUG) || defined(DEBUG)
#define SPD_ASERT(cond, ...)                                  \
    {                                                         \
        if (!(cond))                                          \
        {                                                     \
            mc::log::Log::GetLogger()->critical(__VA_ARGS__); \
            SP_DBG_BREAK();                                   \
        }                                                     \
    }
#else
#define SPD_ASERT(cond, ...)
#endif

namespace mc::log
{
    class Log
    {
    private:
        static std::shared_ptr<spdlog::logger> logger;

    public:
        static std::shared_ptr<spdlog::logger> GetLogger() { return logger; }

    public:
        static void Init();
        static void Shutdown();
    };

}
#endif