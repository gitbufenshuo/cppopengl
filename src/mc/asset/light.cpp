#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <mc/asset/asset_manager.h>
#include <mc/asset/light.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbnode.pb.h>

#include <mc/tools/md5.h>
#include <mc/log/log.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Light::s_scope{"light"};

    Light::Light(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Light()", m_file_path);
            return;
        }
        // load
        load();
        //
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Light>(m_key, this);
        }
    }
    Light::~Light()
    {
        std::cout << " Light Clear" << std::endl;
    }
    Light::Light(const Light &other) : m_pos{other.m_pos},
                                       m_forward{other.m_forward},
                                       m_color{other.m_color},
                                       m_attenuation{other.m_attenuation},
                                       m_kind{other.m_kind}
    {
    }

    MD5SUM Light::GetKey() { return m_key; }
    void Light::SetPos(glm::vec3 pos) { m_pos = pos; }
    void Light::SetForward(glm::vec3 forward) { m_forward = forward; }
    void Light::SetColor(glm::vec3 color) { m_color = color; }
    void Light::SetAttenuation(glm::vec3 attenuation) { m_attenuation = attenuation; }
    void Light::SetKind(Kind kind) { m_kind = kind; }

    const glm::vec3 &Light::GetPos() const { return m_pos; }
    const glm::vec3 &Light::GetForward() const { return m_forward; }
    const glm::vec3 &Light::GetColor() const { return m_color; }
    const glm::vec3 &Light::GetAttenuation() const { return m_attenuation; }
    int Light::GetKind() const
    {
        return static_cast<int>(m_kind);
    }

    std::shared_ptr<Light> Light::Clone() const
    {
        return std::make_shared<Light>(*this);
    }
    void Light::load()
    {
        //
        m_pos.x = m_pb_data.pos().x();
        m_pos.y = m_pb_data.pos().y();
        m_pos.z = m_pb_data.pos().z();
        //
        m_forward.x = m_pb_data.forward().x();
        m_forward.y = m_pb_data.forward().y();
        m_forward.z = m_pb_data.forward().z();
        //
        m_color.x = m_pb_data.color().x();
        m_color.y = m_pb_data.color().y();
        m_color.z = m_pb_data.color().z();
        //
        m_attenuation.x = m_pb_data.attenuation().x();
        m_attenuation.y = m_pb_data.attenuation().y();
        m_attenuation.z = m_pb_data.attenuation().z();
        //
        m_kind = static_cast<Kind>(m_pb_data.kind());
    }

}
