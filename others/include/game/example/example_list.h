#ifndef GAME_EXAMPLE_EXAMPLE_LIST_H
#define GAME_EXAMPLE_EXAMPLE_LIST_H
#include <string>
namespace game::example_list::function_chart
{
    const std::string g_name{"function_chart"};
    int Main();
}
namespace game::example_list::protobuf_test
{
    const std::string g_name{"protobuf_test"};
    int Main();
}
namespace game::example_list::DebugDraw
{
    const std::string g_name{"debug_draw"};
    int Main();
}
namespace game::example_list::gltf_exp
{
    const std::string g_name{"gltf_exp"};
    int Main();
}
namespace game::example_list::cube_transform
{
    const std::string g_name{"cube_transform"};
    int Main();
}

#endif
