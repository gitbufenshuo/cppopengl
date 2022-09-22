#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/art_logic/simple.h>

namespace game
{
    std::shared_ptr<mc::asset::ArtLogic> ArtLogicSimple::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicSimple>()};
        return res;
    }
    void ArtLogicSimple::Register(mc::asset::ArtLogicFactory &af)
    {
        af.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicSimple::~ArtLogicSimple()
    {
    }

    //
    void ArtLogicSimple::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        // m_texture->Use();
        // 传一些 uniform
        {
        }
    }
    void ArtLogicSimple::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicSimple::AddTexture(std::shared_ptr<mc::asset::Texture> texture)
    {
        m_texture = texture;
    }
    const std::string &ArtLogicSimple::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }

}