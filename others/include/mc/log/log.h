#ifndef MC_LOG_LOG_H
#define MC_LOG_LOG_H

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

namespace mc::log
{

    std::shared_ptr<spdlog::logger> Log::logger;

    void Log::Init()
    {
        using wincolor_sink_ptr = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;

        std::vector<wincolor_sink_ptr> sinks;
        sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks[0]->set_pattern("%^%T > [%L] %v%$");

#ifdef MCSYSTEM
        sinks[0]->set_color(spdlog::level::trace, sinks[0]->bold);
        sinks[0]->set_color(spdlog::level::debug, sinks[0]->green);
#else
        sinks[0]->set_color(spdlog::level::trace, sinks[0]->BOLD);
        sinks[0]->set_color(spdlog::level::debug, sinks[0]->GREEN);
#endif

#ifndef SPDBOLD
#define SPDBOLD
#endif
#ifndef SPDGREEN
#define SPDGREEN
#endif

        logger = std::make_shared<spdlog::logger>("sketchpad", begin(sinks), end(sinks));
        spdlog::register_logger(logger);
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }

}

#endif