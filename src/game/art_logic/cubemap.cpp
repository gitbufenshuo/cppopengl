#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/art_logic/cubemap.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicCubemap::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicCubemap>()};
        return res;
    }
    void ArtLogicCubemap::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicCubemap::~ArtLogicCubemap()
    {
    }

    //
    void ArtLogicCubemap::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        m_texture->Use(0);
        // 传一些 uniform
        {
            // 消除里面的 translate
            glm::mat4 view = glm::mat4(glm::mat3(eg->GetCamera()->GetViewMat()));
            // for vertex shader (VP 矩阵)
            m_sp->Uniform("uni_View", view);
            m_sp->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
        }
    }
    void ArtLogicCubemap::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicCubemap::AddTexture(std::shared_ptr<mc::asset::Texture> texture)
    {
        m_texture = texture;
    }
    const std::string &ArtLogicCubemap::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }

}