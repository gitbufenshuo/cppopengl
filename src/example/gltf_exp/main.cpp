#include <iostream>
#include <string>
#include <fstream>
// mc glm
#include <mc/glmex/show.h>

// mc low headers
#include <mc/engine.h>

// game headers

// comm headers
#include <mc/comm/pbdirspec.pb.h>

// asset headers
#include <mc/asset/md5sum.h>
#include <mc/asset/asset_manager.h>

// tools headers
#include <mc/tools/md5.h>

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

namespace game::example_list::gltf_exp
{
    int Main()
    {
        mc::low::Engine gogogo{800, 800, "Hello Scene Load"};
        registArtLogic(gogogo);
        registActLogic(gogogo);
        gogogo.LoadAssetAndCreate("gogogo.pb.data", true);
        gogogo.Run();
        return 0;
    }
}
