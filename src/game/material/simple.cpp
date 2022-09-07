#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/material.h>
#include <game/material/simple.h>

namespace game
{
    // constructors
    MaterialSimple::MaterialSimple() {}
    // virtual
    void MaterialSimple::SetShader(ShaderP shader)
    {
        m_shader = shader;
    }
    void MaterialSimple::PostUniform(Engine *eg, GameObject *gb)
    {
        m_shader->Use();
        // 传一些 uniform
        {
        }
    }
    void MaterialSimple::AddTexture(TextureP texture)
    {
        m_texture = texture;
    }
    void MaterialSimple::ShowMe()
    {
        std::cout << "I am MaterialSimple" << std::endl;
    }
}