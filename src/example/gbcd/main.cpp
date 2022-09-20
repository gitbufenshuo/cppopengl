#include <iostream>
#include <string>
#include <fstream>

// mc low headers
#include <mc/engine.h>
#include <mc/gameobject.h>

// asset headers
#include <mc/asset/act_logic.h>
#include <mc/asset/art_logic.h>

// game headers
#include <game/act_logic/gbcd.h>

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
        game::ActLogicGBCD::Register(am.GetACF());
    }
    // 手动生成场景
    void sceneInitCustom(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        {
            // 生成一个管理 object
            auto newgb{new mc::low::GameObject{&gogogo}};
            newgb->GetTransform()->SetLocalTranslate(0.0f, 5.0f, -5.0f);
            {
                // mesh filter
                auto mf{new mc::low::MeshFilter{}};
                // mf->AddModel(am.Get<mc::asset::Model>("cube-3d-shape.obj.model.pb")); // 可以直接用资源名称获取
                mf->AddModel(am.Get<mc::asset::Model>("52517.model.pb")); // 可以直接用资源名称获取
                // mesh render
                auto mr{new mc::low::MeshRender{}};
                mr->SetGameobject(newgb);
                mr->SetMaterial(am.Get<mc::asset::Material>()); // 暂时
                newgb->SetMeshFilter(mf);
                newgb->SetMeshRender(mr);
            }
            {
                // act logic
                auto &act_factory{am.GetACF()};
                auto realActLogic{act_factory.Create(newgb, "mc::asset::ActLogicCamera", "")};
                newgb->AddAct(realActLogic);
            }
            gogogo.AddGameobject(newgb);
        }
        {
            // 生成一个 普通 object
            auto newgb{new mc::low::GameObject{&gogogo}};
            newgb->GetTransform()->SetLocalTranslate(0.0f, 0.0f, 0.0f);
            {
                // mesh filter
                auto mf{new mc::low::MeshFilter{}};
                mf->AddModel(am.Get<mc::asset::Model>("cube-3d-shape.obj.model.pb")); // 可以直接用资源名称获取
                // mesh render
                auto mr{new mc::low::MeshRender{}};
                mr->SetGameobject(newgb);
                mr->SetMaterial(am.Get<mc::asset::Material>()); // 暂时
                newgb->SetMeshFilter(mf);
                newgb->SetMeshRender(mr);
            }
            {
                // act logic
                auto &act_factory{am.GetACF()};
                auto realActLogic{act_factory.Create(newgb, "game::act_logic::ActLogicGBCD", "")};
                newgb->AddAct(realActLogic);
            }
            gogogo.AddGameobject(newgb);
        }
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
        sceneInitCustom(gogogo);
        gogogo.Run();
        return 0;
    }
}
