#include <iostream>
#include <string>
#include <fstream>

// mc low headers
#include <mc/engine.h>
#include <mc/gameobject.h>
#include <mc/camera_skybox.h>

// asset headers
#include <mc/asset/texture.h>
#include <mc/asset/shader_program.h>
#include <mc/asset/model.h>
#include <mc/asset/act_logic.h>
#include <mc/asset/art_logic.h>

// game headers
#include <game/act_logic/gbcd.h>
#include <game/act_logic/light_source.h>

// game headers
#include <game/art_logic/cubemap.h> // skybox

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
        game::ArtLogicCubemap::Register(am.GetARF());
    }
    void registActLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ActLogicCamera::Register(am.GetACF());
        game::ActLogicGBCD::Register(am.GetACF());
        game::ActLogicLightSource::Register(am.GetACF());
    }
    // 手动创建一个skybox
    void createSkybox(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        auto &art_factory{am.GetARF()};

        //
        auto newskybox{new mc::low::Skybox{&gogogo}};
        gogogo.GetCamera()->SetSkybox(newskybox);
        //
        newskybox->SetArtLogic(art_factory.Create("game::art_logic::ArtLogicCubemap", ""));
        newskybox->AddTexture(am.Get<mc::asset::Texture>("skybox.cubemap.pb"));
        newskybox->SetShaderProgram(std::make_shared<mc::asset::ShaderProgram>(
            mc::low::Skybox::s_vcode, mc::low::Skybox::s_fcode));
        newskybox->SetModel(mc::asset::Model::CreateCubemap());
    }
    // 手动生成场景
    void sceneInitCustom(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        {
            // 生成一个管理 object
            auto newgb{new mc::low::GameObject{&gogogo}};
            newgb->GetTransform()->SetLocalTranslate(0.0f, 5.0f, -5.0f);
            newgb->GetTransform()->SetLocalScale(0.3f, 0.3f, 0.3f);
            {
                // mesh filter
                auto mf{new mc::low::MeshFilter{}};
                mf->AddModel(am.Get<mc::asset::Model>("52517.model.pb")); // 可以直接用资源名称获取
                // mesh render
                auto mr{new mc::low::MeshRender{}};
                mr->SetGameobject(newgb);
                mr->SetMaterial(std::make_shared<mc::asset::Material>(*am.Get<mc::asset::Material>())); // 复制一份
                {
                    // 改变uniform 让这个东西巨亮 用来代表光源
                    static_cast<mc::asset::ArtLogicPhong *>(mr->GetMaterial()->GetArtLogic().get())->SetAmbient(1.0f);
                }
                newgb->SetMeshFilter(mf);
                newgb->SetMeshRender(mr);
            }
            {
                // act logic
                auto &act_factory{am.GetACF()};
                auto realActLogic{act_factory.Create(newgb, "mc::asset::ActLogicCamera", "")};
                newgb->AddAct(realActLogic);
                auto light_source_lg{act_factory.Create(newgb, game::ActLogicLightSource::s_class_name, "")};
                newgb->AddAct(light_source_lg);
            }
            gogogo.AddGameobject(newgb);
        }
        {
            // 生成三个 普通 object
            float pos[]{-6.0f, 0.0f, 6.0f};
            for (int ge = 0; ge < 3; ++ge)
            {
                auto newgb{new mc::low::GameObject{&gogogo}};
                newgb->GetTransform()->SetLocalTranslate(pos[ge], 0.0f, 0.0f);
                {
                    // mesh filter
                    auto mf{new mc::low::MeshFilter{}};
                    mf->AddModel(am.Get<mc::asset::Model>("low-poly-fox-by-pixelmannen.obj.model.pb")); // 可以直接用资源名称获取
                    // mesh render
                    auto mr{new mc::low::MeshRender{}};
                    mr->SetGameobject(newgb);
                    mr->SetMaterial(std::make_shared<mc::asset::Material>(*am.Get<mc::asset::Material>())); // 复制一份
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
        {
            // 搞一个地面
            auto newgb{new mc::low::GameObject{&gogogo}};
            newgb->GetTransform()->SetLocalTranslate(0.0f, -2.0f, 0.0f);
            newgb->GetTransform()->SetLocalScale(20.0f, 1.0f, 16.0f);
            {
                // mesh filter
                auto mf{new mc::low::MeshFilter{}};
                mf->AddModel(am.Get<mc::asset::Model>("52517.model.pb")); // 可以直接用资源名称获取
                // mesh render
                auto mr{new mc::low::MeshRender{}};
                mr->SetGameobject(newgb);
                mr->SetMaterial(std::make_shared<mc::asset::Material>(*am.Get<mc::asset::Material>())); // 复制一份
                newgb->SetMeshFilter(mf);
                newgb->SetMeshRender(mr);
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
        createSkybox(gogogo); // 测试 skybox
        gogogo.Run();
        return 0;
    }
}