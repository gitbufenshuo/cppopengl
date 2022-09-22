#include <cassert>
#include <vector>
#include <memory>
#include <iostream>

#include <game/act_logic/gbcd.h>
#include <mc/asset/act_logic.h>

namespace
{
    int g_gbcount{0};
    using move_func = void (*)(mc::low::Transform *tr, glm::vec3 dir);
    void move_0(mc::low::Transform *tr, glm::vec3 dir)
    {
        tr->Move(dir, mc::low::Space::World);
    }
    void move_1(mc::low::Transform *tr, glm::vec3 dir)
    {
        tr->LookAt(glm::vec3{0.0f, 0.0f, 0.0f});
        tr->Move(glm::vec3{0.05f, 0.05f, 0.05f});
    }
    std::vector<move_func> move_func_list{
        move_0,
        move_1};
    void createNew(mc::low::Engine *eg, glm::vec3 pos)
    {
        // 生成一个 普通 object
        auto &am{*eg->GetAM()};
        auto newgb{new mc::low::GameObject{eg}};
        newgb->GetTransform()->SetLocalTranslate(pos.x, pos.y, pos.z);
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
            if (m_outline == 1)
            {
                m_gb->GetMeshRender()->GetMaterial()->SetRenderBit(1, true);
            }
        }
    }

    void ActLogicGBCD::move(double delta_time)
    {
        auto worlpos{m_tr->GetWorldPos()};
        auto distance_ori{glm::length(worlpos)};
        if (distance_ori > 15.0f)
        {
            moving_state = 1;
        }
        else if (distance_ori < 0.5f)
        {
            moving_state = 0;
        }
        move_func_list[moving_state](m_tr, m_outdir);
    }
    void ActLogicGBCD::life(double delta_time)
    {
        m_time += static_cast<float>(delta_time);
        // std::cout << m_time << std::endl;
        if (m_time < 2.0f)
        {
            return;
        }
        std::cout << "gameobject_count: " << m_eg->GameObjectSize() << " " << delta_time << std::endl;
        m_time = 0.0f;
        // 生成三个新的
        if (g_gbcount > 10)
        {
            return;
        }
        auto worldPos{m_tr->GetWorldPos()};
        createNew(m_eg, -worldPos.x, worldPos.y, worldPos.z);
        createNew(m_eg, worldPos.x, -worldPos.y, worldPos.z);
        createNew(m_eg, worldPos.x, worldPos.y, -worldPos.z);
        // 将自身del
        m_gb->Destroy();
    }

}