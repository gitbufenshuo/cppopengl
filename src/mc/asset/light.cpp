#include <string>
#include <iostream>
#include <filesystem>

#include <mc/asset/asset_manager.h>
#include <mc/asset/light.h>
#include <mc/asset/md5sum.h>

#include <mc/tools/md5.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Light::s_scope{"light"};

    Light::Light(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {
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

    const glm::vec3 &Light::GetPos() const { return m_pos; }
    const glm::vec3 &Light::GetForward() const { return m_forward; }
    const glm::vec3 &Light::GetColor() const { return m_color; }
    const glm::vec3 &Light::GetAttenuation() const { return m_attenuation; }

    std::shared_ptr<Light> Light::Clone() const
    {
        return std::make_shared<Light>(*this);
    }

}
