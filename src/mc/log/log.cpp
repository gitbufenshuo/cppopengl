#include <mc/log/log.h>

namespace mc::log
{

    std::shared_ptr<spdlog::logger> Log::logger;

    void Log::Init()
    {
        using wincolor_sink_ptr = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;

        std::vector<wincolor_sink_ptr> sinks;
        sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks[0]->set_pattern("%^%T > [%L] %v%$");

        sinks[0]->set_color(spdlog::level::trace, sinks[0]->COLOR_BOLD);
        sinks[0]->set_color(spdlog::level::debug, sinks[0]->COLOR_GREEN);

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