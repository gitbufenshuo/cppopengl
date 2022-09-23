#include <cassert>
#include <vector>
#include <memory>
#include <iostream>

#include <game/act_logic/gbcd.h>
#include <mc/asset/act_logic.h>

namespace
{
    std::vector<std::shared_ptr<mc::asset::Model>> g_model_list;
    void append_model(std::shared_ptr<mc::asset::Model> input)
    {
        g_model_list.push_back(input);
    }
    int g_gbcount{0};
    void createNew(mc::low::Engine *eg, glm::vec3 pos)
    {
        auto &am{*eg->GetAM()};
        // 生成一个 普通 object
        auto newgb{new mc::low::GameObject{eg}};
        newgb->GetTransform()->SetLocalTranslate(pos.x, pos.y, pos.z);
        {
            // mesh filter
            auto mf{new mc::low::MeshFilter{}};
            mf->AddModel(g_model_list[0]); // 可以直接用资源名称获取
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
        eg->AddGameobject(newgb);
    }
    void createNew(mc::low::Engine *eg, float x, float y, float z)
    {
        createNew(eg, glm::vec3{x, y, z});
    }

}

namespace game
{
    std::shared_ptr<mc::asset::ActLogic> ActLogicGBCD::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicGBCD>()};
        res->m_gb = gb;
        res->m_tr = gb->GetTransform();
        res->m_eg = gb->GetEngine();
        res->m_outline = (++g_gbcount) % 2;
        return res;
    }
    void ActLogicGBCD::Register(mc::asset::ActLogicFactory &acf)
    {
        acf.Register("game::act_logic::ActLogicGBCD", createFunc);
    }
    ActLogicGBCD::~ActLogicGBCD()
    {
    }
    void ActLogicGBCD::Update(double delta_time)
    {
        accArt();
        move(delta_time);
        life(delta_time);
        changeModel();
    }
    void ActLogicGBCD::BeforeRenderUpdate(double delta_time, unsigned int layer)
    {
        if (m_phong_ins)
        {
            if (layer == 1)
            {
                m_phong_ins->SetOutline(1);
            }
            else
            {
                m_phong_ins->SetOutline(0);
            }
        }
    }
    void ActLogicGBCD::AfterRenderUpdate(double delta_time, unsigned int layer) {}
    //
    void ActLogicGBCD::accArt()
    {
        if (!m_phong_ins)
        {
            auto arl{m_gb->GetMeshRender()->GetMaterial()->GetArtLogic()};
            m_phong_ins = static_cast<mc::asset::ArtLogicPhong *>(arl.get());
            // if (m_outline == 1)
            // {
            //     m_gb->GetMeshRender()->GetMaterial()->SetRenderBit(1, true);
            // }
        }
    }
    void ActLogicGBCD::changeModel()
    {
        // 初始化g_model_list
        if (g_model_list.empty())
        {
            auto &am{*m_gb->GetEngine()->GetAM()};
            append_model(am.Get<mc::asset::Model>("52517.model.pb"));
            append_model(am.Get<mc::asset::Model>("low-poly-fox-by-pixelmannen.obj.model.pb"));
        }
        if (static_cast<int>(m_time) % 2 == 0)
        {
            m_gb->GetMeshFilter()->SetModel(0, g_model_list[0]);
        }
        else
        {
            m_gb->GetMeshFilter()->SetModel(0, g_model_list[1]);
        }
    }

    void ActLogicGBCD::move(double delta_time)
    {
        m_gb->GetTransform()->Rotate(1.0f, 0.0f, 0.0f, 1.0f * delta_time);
        return;
    }
    void ActLogicGBCD::life(double delta_time)
    {
        m_time += static_cast<float>(delta_time);
        // std::cout << m_time << std::endl;
        // if (m_time < 2.0f)
        // {
        //     return;
        // }
        // std::cout << "gameobject_count: " << m_eg->GameObjectSize() << " " << delta_time << std::endl;
        // m_time = 0.0f;
        // // 生成三个新的
        // if (g_gbcount > 10)
        // {
        //     return;
        // }
        // auto worldPos{m_tr->GetWorldPos()};
        // createNew(m_eg, -worldPos.x, worldPos.y, worldPos.z);
        // createNew(m_eg, worldPos.x, -worldPos.y, worldPos.z);
        // createNew(m_eg, worldPos.x, worldPos.y, -worldPos.z);
        // // 将自身del
        // m_gb->Destroy();
    }

}