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
    const std::string ArtLogic::s_scope{"art_logic"};

    ArtLogic::ArtLogic(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                      m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::ArtLogic()", m_file_path);
            return;
        }
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<ArtLogic>(m_key, this);
        }
    }
    ArtLogic::~ArtLogic()
    {
        std::cout << " ArtLogic Clear" << std::endl;
    }
    MD5SUM ArtLogic::GetKey() { return m_key; }
    const std::string &ArtLogic::GetLogicName()
    {
        return m_pb_data.logic_class();
    }
    const std::string &ArtLogic::GetBinData()
    {
        return m_pb_data.properties();
    }

}

namespace mc::asset
{
    void ArtLogicFactory::Register(const std::string &class_name, CreateFunc cf)
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
    ArtLogicFactory::CreateFunc ArtLogicFactory::getFunc(const std::string &class_name)
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

    std::shared_ptr<ArtLogic> ArtLogicFactory::Create(const std::string &class_name, const std::string &bin_data)
    {
        auto func{getFunc(class_name)};
        if (!func)
        {
            return std::shared_ptr<ArtLogic>{nullptr};
        }
        //
        return func(bin_data);
    }
}

namespace mc::asset
{
    const std::string ArtLogicPhong::s_class_name{"mc::asset::ArtLogicPhong"};
    std::shared_ptr<ArtLogic> ArtLogicPhong::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicPhong>()};
        // "1,1,1,1,1,1,1,1,1,1"
        std::string col;
        std::stringstream row_stream{bin_data};
        int index{0};
        while (std::getline(row_stream, col, ','))
        {
            switch (index++)
            {
            case 0:
                res->m_ambient.x = std::stof(col);
                break;
            case 1:
                res->m_ambient.y = std::stof(col);
                break;
            case 2:
                res->m_ambient.z = std::stof(col);
                break;
            case 3:
                res->m_diffuse.x = std::stof(col);
                break;
            case 4:
                res->m_diffuse.y = std::stof(col);
                break;
            case 5:
                res->m_diffuse.z = std::stof(col);
                break;
            case 6:
                res->m_specular.x = std::stof(col);
                break;
            case 7:
                res->m_specular.y = std::stof(col);
                break;
            case 8:
                res->m_specular.z = std::stof(col);
                break;
            case 9:
                res->m_shininess = std::stof(col);
                break;

            default:
                break;
            }
        }
        return res;
    }
    void ArtLogicPhong::Register(ArtLogicFactory &arf)
    {
        arf.Register(s_class_name, createFunc);
    }

    // public virtual
    ArtLogicPhong::~ArtLogicPhong()
    {
    }
    std::shared_ptr<ArtLogic> ArtLogicPhong::Clone()
    {
        return std::make_shared<ArtLogicPhong>(*this);
    }
    void ArtLogicPhong::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        {
            m_sp->Uniform("uni_ourTexture", 0);
            m_sp->Uniform("uni_ourNormal", 1);
            m_sp->Uniform("uni_ourParallax", 2);
            m_texture->Use(0);
            m_normal->Use(1);
            m_parallax->Use(2);
            // light map bind
            std::string uni_shadow_map{"uni_shadow_map[x]"};

            for (int index = 0; index < eg->LightSize(); ++index)
            {
                uni_shadow_map[15] = '0' + static_cast<char>(index);
                eg->GetLight(index)->UseTexture(index + 3);
                m_sp->Uniform(uni_shadow_map.data(), index + 3);
            }
        }
        // 传一些 uniform
        {
            m_sp->Uniform("uni_outline", m_outline);
            m_sp->Uniform("uni_View", eg->GetCamera()->GetViewMat());
            m_sp->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
            m_sp->Uniform("uni_viewPos", eg->GetCamera()->GetTransform()->GetWorldPos());
        }
        {
            m_sp->Uniform("uni_material.ambient", m_ambient);
            m_sp->Uniform("uni_material.diffuse", m_diffuse);
            m_sp->Uniform("uni_material.specular", m_specular);
            m_sp->Uniform("uni_material.shininess", m_shininess);
        }
        {
            m_sp->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
            m_sp->Uniform("uni_Normal", gb->GetTransform()->GetNormalMat());
        }
        {
            // lights
            std::string uni_pos{"uni_light[x].pos"};
            std::string uni_forward{"uni_light[x].forward"};
            std::string uni_color{"uni_light[x].color"};
            std::string uni_attenuation{"uni_light[x].attenuation"};
            std::string uni_cutoff{"uni_light[x].cutoff"};
            std::string uni_kind{"uni_light[x].kind"};
            std::string uni_light_mat{"uni_light_mat[x]"}; // light space mat
            for (int index = 0; index < eg->LightSize(); ++index)
            {
                auto _light{eg->GetLight(index)};
                auto _kind{_light->GetKind()};
                auto &_pos{_light->GetPos()};
                auto &_color{_light->GetColor()};
                auto &_forward{_light->GetForward()};

                if (_kind == 0)
                {
                    // dir light
                    uni_pos[10] = '0' + static_cast<char>(index);
                    uni_color[10] = '0' + static_cast<char>(index);
                    uni_kind[10] = '0' + static_cast<char>(index);
                    uni_light_mat[14] = '0' + static_cast<char>(index);

                    m_sp->Uniform(uni_pos.data(), _pos);
                    m_sp->Uniform(uni_color.data(), _color);
                    m_sp->Uniform(uni_kind.data(), _kind);
                    m_sp->Uniform(uni_light_mat.data(), _light->GetLightMat());
                }
                else if (_kind == 1)
                {
                    // point light
                    uni_pos[10] = '0' + static_cast<char>(index);
                    uni_color[10] = '0' + static_cast<char>(index);
                    uni_kind[10] = '0' + static_cast<char>(index);
                    uni_attenuation[10] = '0' + static_cast<char>(index);

                    m_sp->Uniform(uni_pos.data(), _pos);
                    m_sp->Uniform(uni_color.data(), _color);
                    m_sp->Uniform(uni_kind.data(), _kind);
                    m_sp->Uniform(uni_attenuation.data(), glm::vec3{1.0f, 0.1f, 0.1f});
                }
                else
                {
                    // spot light
                    uni_pos[10] = '0' + static_cast<char>(index);
                    uni_color[10] = '0' + static_cast<char>(index);
                    uni_kind[10] = '0' + static_cast<char>(index);
                    uni_attenuation[10] = '0' + static_cast<char>(index);
                    uni_forward[10] = '0' + static_cast<char>(index);
                    uni_cutoff[10] = '0' + static_cast<char>(index);
                    uni_light_mat[14] = '0' + static_cast<char>(index);
                    // uni_light_mat
                    m_sp->Uniform(uni_pos.data(), _pos);
                    m_sp->Uniform(uni_color.data(), _color);
                    m_sp->Uniform(uni_kind.data(), _kind);
                    m_sp->Uniform(uni_attenuation.data(), glm::vec3{1.0f, 0.05f, 0.05f});
                    m_sp->Uniform(uni_forward.data(), _forward);
                    m_sp->Uniform(uni_cutoff.data(), glm::vec3{glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)), 1.0f});
                    m_sp->Uniform(uni_light_mat.data(), _light->GetLightMat());
                }
            }
        }
    }
    void ArtLogicPhong::SetShaderProgram(std::shared_ptr<ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicPhong::AddTexture(std::shared_ptr<Texture> texture)
    {
        if (!m_texture)
        {
            m_texture = texture;
        }
        else
        {
            if (!m_normal)
            {
                m_normal = texture;
            }
            else
            {
                m_parallax = texture;
            }
        }
    }
    const std::string &ArtLogicPhong::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }
    // custom public
    void ArtLogicPhong::SetOutline(int outline)
    {
        m_outline = outline;
    }
    void ArtLogicPhong::SetAmbient(float v1)
    {
        m_ambient.x = v1;
        m_ambient.y = v1;
        m_ambient.z = v1;
    }

}