namespace mc::low
{
    class Skybox;
}
#ifndef MC_LOW_CAMERA_SKYBOX_H
#define MC_LOW_CAMERA_SKYBOX_H

#include <memory>

#include <mc/engine.h>

#include <mc/asset/texture.h>
#include <mc/asset/shader_program.h>
#include <mc/asset/art_logic.h>

namespace mc::low
{
    class Skybox
    {
    public:
        Skybox(Engine *);
        void AddTexture(std::shared_ptr<mc::asset::Texture>);
        void SetArtLogic(std::shared_ptr<mc::asset::ArtLogic>);
        void SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram>);
        void SetModel(std::shared_ptr<mc::asset::Model>);
        void Draw();

    public:
        static const char *s_vcode;
        static const char *s_fcode;

    private:
        std::shared_ptr<mc::asset::ArtLogic> m_art_logic;
        std::shared_ptr<mc::asset::Model> m_model;
        Engine *m_engine;
    };
}
#endif