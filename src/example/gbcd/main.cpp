#include <iostream>
#include <string>
#include <fstream>

// mc low headers
#include <mc/engine.h>

// log
#include <mc/log/log.h>

namespace
{
    void registArtLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ArtLogicPhong::Register(am.GetARF());
    }
    void registActLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ActLogicCamera::Register(am.GetACF());
    }

}

namespace game::example_list::gbcd
{
    int Main()
    {
        mc::low::Engine gogogo{800, 800, "Hello gbcd"};
        registArtLogic(gogogo);
        registActLogic(gogogo);
        gogogo.LoadAssetAndCreate("gogogo.pb.data", false);
        gogogo.Run();
        return 0;
    }
}
