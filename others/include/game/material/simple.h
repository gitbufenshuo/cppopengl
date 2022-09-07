#ifndef GAME_MA_SIMPLE_H
#define GAME_MA_SIMPLE_H

#include <mc/material.h>
#include <mc/texture_store.h>
#include <mc/shader_store.h>
#include <mc/engine.h>

namespace game
{
    class MaterialSimple : public mc::low::Material
    {
    public:
        using ShaderP = mc::low::ShaderP;
        using TextureP = mc::low::TextureP;
        using Engine = mc::low::Engine;
        using GameObject = mc::low::GameObject;

    private:
        ShaderP m_shader;
        TextureP m_texture;

    public:
        MaterialSimple();
        ~MaterialSimple() override {}

    public:
        void PostUniform(Engine *eg, GameObject *gb) override;
        void SetShader(ShaderP shader) override;
        void AddTexture(TextureP texture) override;
        void ShowMe() override;
    };

}
#endif