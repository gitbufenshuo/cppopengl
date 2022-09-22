#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

// glad
#include <glad/glad.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/model.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string ActLogic::s_scope{"act_logic"};

    ActLogic::ActLogic(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                      m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::ActLogic()", m_file_path);
            return;
        }
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<ActLogic>(m_key, this);
        }
    }
    ActLogic::~ActLogic()
    {
        // std::cout << " ActLogic Clear" << std::endl;
    }
    MD5SUM ActLogic::GetKey() { return m_key; }
    const std::string &ActLogic::GetLogicName()
    {
        return m_pb_data.logic_class();
    }
    const std::string &ActLogic::GetBinData()
    {
        return m_pb_data.properties();
    }

}

namespace mc::asset
{
    void ActLogicFactory::Register(const std::string &class_name, CreateFunc cf)
    {
        // 为什么不用 哈希表呢，因为这玩意不会很多
        // 也不会用的很多，不属于热点代码
        // 如果最后变成热点代码
        // 届时再改成 unordered map
        for (const auto &one_entry : m_holder)
        {
            if (0 == one_entry.first.compare(class_name))
            {
                return;
            }
        }
        //
        m_holder.push_back(std::pair{class_name, cf});
    }
    ActLogicFactory::CreateFunc ActLogicFactory::getFunc(const std::string &class_name)
    {
        for (const auto &one_entry : m_holder)
        {
            if (0 == one_entry.first.compare(class_name))
            {
                return one_entry.second;
            }
        }
        return nullptr;
    }

    std::shared_ptr<ActLogic> ActLogicFactory::Create(mc::low::GameObject *gb, const std::string &class_name, const std::string &bin_data)
    {
        auto func{getFunc(class_name)};
        if (!func)
        {
            return std::shared_ptr<ActLogic>{nullptr};
        }
        //
        return func(gb, bin_data);
    }
}

namespace mc::asset
{

    std::shared_ptr<ActLogic> ActLogicCamera::createFunc(mc::low::GameObject *gb, const std::string &bin_data)
    {
        auto res{std::make_shared<ActLogicCamera>()};
        res->m_gb = gb;
        res->m_ctl_transform = gb->GetEngine()->GetCamera()->GetTransform();
        return res;
    }

    ActLogicCamera::~ActLogicCamera() {}

    void ActLogicCamera::Register(ActLogicFactory &acf)
    {
        acf.Register("mc::asset::ActLogicCamera", createFunc);
    }

    void ActLogicCamera::Update(double delta_time)
    {
        float speed = 1.0f * static_cast<float>(delta_time);
        float xdiff = static_cast<float>(mc::low::Engine::s_c_xdiff);
        m_now_yaw -= xdiff * speed * 3.0f;
        float ydiff = static_cast<float>(mc::low::Engine::s_c_ydiff);
        m_now_pitch -= ydiff * speed * 3.0f;
        m_now_pitch = std::clamp(m_now_pitch, -89.0f, 89.0f);
        m_ctl_transform->SetLocalEuler(m_now_pitch, m_now_yaw, 0.0f);
        // camera translate
        speed *= 15.0f;
        if (mc::low::Engine::s_keyinput.KeyStateDown(65))
        {
            // A key
            m_ctl_transform->Move(glm::vec3{-speed, 0.0f, 0.0f});
            // m_ctl_transform->Move(glm::vec3{-speed, 0.0f, 0.0f}, mc::low::Space::World);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(68))
        {
            // D key
            m_ctl_transform->Move(glm::vec3{speed, 0.0f, 0.0f});
            // m_ctl_transform->Move(glm::vec3{speed, 0.0f, 0.0f}, mc::low::Space::World);
        }

        if (mc::low::Engine::s_keyinput.KeyStateDown(87))
        {
            // W key
            m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, -speed});
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, -speed}, mc::low::Space::World);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(83))
        {
            // S key
            m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, speed});
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, speed}, mc::low::Space::World);
        }

        if (mc::low::Engine::s_keyinput.KeyStateDown(69))
        {
            // E key
            m_ctl_transform->Move(glm::vec3{0.0f, -speed, 0.0f}, mc::low::Space::World);
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, -speed}, mc::low::Space::World);
        }
        else if (mc::low::Engine::s_keyinput.KeyStateDown(81))
        {
            // Q key
            m_ctl_transform->Move(glm::vec3{0.0f, speed, 0.0f}, mc::low::Space::World);
            // m_ctl_transform->Move(glm::vec3{0.0f, 0.0f, speed}, mc::low::Space::World);
        }
    }
    void ActLogicCamera::BeforeRenderUpdate(double delta_time) {}
    void ActLogicCamera::AfterRenderUpdate(double delta_time) {}
};
