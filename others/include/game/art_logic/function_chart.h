#ifndef GAME_FUNCTION_CHART_H
#define GAME_FUNCTION_CHART_H

#include <memory>

#include <mc/engine.h>

#include <mc/asset/art_logic.h>

namespace game
{
    class ArtLogicFunctionChart : public mc::asset::ArtLogic
    {
    private:
        std::shared_ptr<mc::asset::ShaderProgram> m_sp;
        std::shared_ptr<mc::asset::Texture> m_texture;

    private:
        static std::shared_ptr<ArtLogic> createFunc(const std::string &bin_data);

    public:
        ~ArtLogicFunctionChart() override;

    public:
        static void Register(mc::asset::ArtLogicFactory &af);

    public:
        // virtual
        void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) override;
        void SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp) override;
        void AddTexture(std::shared_ptr<mc::asset::Texture> texture) override;
        void ShowMe() override;
    };

}
#endif