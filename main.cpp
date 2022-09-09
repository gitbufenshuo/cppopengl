#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>

#include <game/example/example_list.h>
#pragma region LOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define CORE_INFO(...) ::core::Log::GetLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::core::Log::GetLogger()->warn(__VA_ARGS__)
#define CORE_DEBUG(...) ::core::Log::GetLogger()->debug(__VA_ARGS__)
#define CORE_TRACE(...) ::core::Log::GetLogger()->trace(__VA_ARGS__)
#define CORE_ERROR(...) ::core::Log::GetLogger()->error(__VA_ARGS__)

// exceptions, error handling and varying levels of logging is part of the app's normal workflow
// assertions however, must hold in any correct release build, they only apply to the debug mode

#if defined(_DEBUG) || defined(DEBUG)
#define CORE_ASERT(cond, ...)                                \
    {                                                        \
        if (!(cond))                                         \
        {                                                    \
            ::core::Log::GetLogger()->critical(__VA_ARGS__); \
            SP_DBG_BREAK();                                  \
        }                                                    \
    }
#else
#define CORE_ASERT(cond, ...)
#endif

namespace core
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

namespace core
{

    std::shared_ptr<spdlog::logger> Log::logger;

    void Log::Init()
    {
        using wincolor_sink_ptr = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;

        std::vector<wincolor_sink_ptr> sinks;
        sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks[0]->set_pattern("%^%T > [%L] %v%$");
#ifndef SPDBOLD
#define SPDBOLD
#endif
#ifndef SPDGREEN
#define SPDGREEN
#endif
        sinks[0]->set_color(spdlog::level::trace, sinks[0]->SPDBOLD);
        sinks[0]->set_color(spdlog::level::debug, sinks[0]->SPDGREEN);

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
#pragma endregion

using entry_func = int (*)();
void reg_entry(std::unordered_map<std::string, entry_func> &entry_list)
{
    {
        entry_func one{game::example_list::function_chart::Main};
        entry_list.insert(
            std::pair(
                game::example_list::function_chart::g_name,
                one));
    }
    {
        entry_func one{game::example_list::protobuf_test::Main};
        entry_list.insert(
            std::pair(
                game::example_list::protobuf_test::g_name,
                one));
    }
    {
        entry_func one{game::example_list::DebugDraw::Main};
        entry_list.insert(
            std::pair(
                game::example_list::DebugDraw::g_name,
                one));
    }
    {
        entry_func one{game::example_list::gltf_exp::Main};
        entry_list.insert(
            std::pair(
                game::example_list::gltf_exp::g_name,
                one));
    }
}

int main(int argc, char *argv[])
{

    ::core::Log::Init();
    CORE_INFO("Start The Log");
    if (argc == 1)
    {
        std::cout << "请输入想要运行的程序\n"
                  << "例如(mac): ./mc.out function_chart" << std::endl
                  << "例如(mac): ./mc.out protobuf_test" << std::endl
                  << "例如(mac): ./mc.out gltf_exp" << std::endl
                  << "例如(windows): ./mc.out.exe function_chart" << std::endl
                  << "例如(windows): ./mc.out.exe protobuf_test" << std::endl
                  << "例如(windows): ./mc.out.exe gltf_exp" << std::endl;
        return 0;
    }
    std::unordered_map<std::string, entry_func> entry_list;
    reg_entry(entry_list);
    std::string e_name{argv[1]};
    auto func = entry_list[e_name];
    return func();
}