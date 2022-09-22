#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>

#include <game/art_logic/phong_spot.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicPhongSpot::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicPhongSpot>()};
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
    void ArtLogicPhongSpot::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }

    void ArtLogicPhongSpot::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        m_texture->Use();
        // 传一些 uniform
        {
            // for vertex shader (MVP 矩阵)
            m_sp->Uniform("uni_View", eg->GetCamera()->GetViewMat());
            m_sp->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
            m_sp->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
            // for fragment shader (camera)
            m_sp->Uniform("uni_viewPos", eg->GetCamera()->GetTransform()->GetWorldPos());
            // for fragment shader (light)
            m_sp->Uniform("uni_spotLight.position", eg->GetCamera()->GetTransform()->GetWorldPos());
            m_sp->Uniform("uni_spotLight.direction", m_spot_light.direction);
            m_sp->Uniform("uni_spotLight.cutOff", m_spot_light.cutOff);
            m_sp->Uniform("uni_spotLight.outerCutOff", m_spot_light.outerCutOff);
            m_sp->Uniform("uni_spotLight.constant", m_spot_light.constant);
            m_sp->Uniform("uni_spotLight.linear", m_spot_light.linear);
            m_sp->Uniform("uni_spotLight.quadratic", m_spot_light.quadratic);
            m_sp->Uniform("uni_spotLight.ambient", m_spot_light.ambient);
            m_sp->Uniform("uni_spotLight.diffuse", m_spot_light.diffuse);
            m_sp->Uniform("uni_spotLight.specular", m_spot_light.specular);
            // for fragment shader (material)
            m_sp->Uniform("uni_material.specular", m_specular);
            m_sp->Uniform("uni_material.m_shininess", m_shininess);
        }
    }
    void ArtLogicPhongSpot::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicPhongSpot::AddTexture(std::shared_ptr<mc::asset::Texture> texture)
    {
        m_texture = texture;
    }
    const std::string &ArtLogicPhongSpot::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }

}