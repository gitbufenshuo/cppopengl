#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>

#include <game/art_logic/blinn_phong_point.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicBlinnPhongPoint::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicBlinnPhongPoint>()};
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
    void ArtLogicBlinnPhongPoint::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicBlinnPhongPoint::~ArtLogicBlinnPhongPoint()
    {
    }

    // virtual
    void ArtLogicBlinnPhongPoint::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        m_texture->Use();
        // 传一些 uniform
        {
            m_sp->Uniform("ma_View", eg->GetCamera()->GetViewMat());
            m_sp->Uniform("ma_Proj", eg->GetCamera()->GetProjMat());
            m_sp->Uniform("lightPos", eg->GetLightPos());
            m_sp->Uniform("lightColor", eg->GetLightColor());
        }
        {
            m_sp->Uniform("material.ambient", m_ambient);
            m_sp->Uniform("material.diffuse", m_diffuse);
            m_sp->Uniform("material.specular", m_specular);
            m_sp->Uniform("material.shininess", m_shininess);
        }
        {
            m_sp->Uniform("ma_Model", gb->GetTransform()->GetWorldMat());
        }
    }
    void ArtLogicBlinnPhongPoint::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicBlinnPhongPoint::AddTexture(std::shared_ptr<mc::asset::Texture> texture)
    {
        m_texture = texture;
    }
    const std::string &ArtLogicBlinnPhongPoint::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }
}