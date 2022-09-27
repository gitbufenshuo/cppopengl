#ifndef GAME_ART_LOGIC_SHADOW_GENERATE_H
#define GAME_ART_LOGIC_SHADOW_GENERATE_H

#include <memory>
#include <string>

#include <mc/engine.h>

#include <mc/asset/art_logic.h>
#include <mc/asset/light.h>

namespace game
{
    class ArtLogicShadowGenerate : public mc::asset::ArtLogic
    {
    private:
        std::shared_ptr<mc::asset::ShaderProgram> m_sp;

    public:
        static inline const std::string s_class_name{"game::art_logic::ArtLogicShadowGenerate"};

    private:
        static std::shared_ptr<mc::asset::ArtLogic> createFunc(const std::string &bin_data);

    public:
        ~ArtLogicShadowGenerate() override;

    public:
        static void Register(mc::asset::ArtLogicFactory &af);

    public:
        // virtual
        void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) override;
        void SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp) override;
        const std::string &ShowMe() override;

    private:
        std::shared_ptr<mc::asset::Light> m_light;

    public:
        void SetLight(std::shared_ptr<mc::asset::Light> _light);

    public:
        static const char *s_vcode;
        static const char *s_fcode;
    };

}
#endif