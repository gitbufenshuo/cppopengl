#ifndef GAME_BLINN_PHONG_POINT_H
#define GAME_BLINN_PHONG_POINT_H

// std
#include <memory>
#include <string>

// low
#include <mc/engine.h>

// asset
#include <mc/asset/shader_program.h>
#include <mc/asset/texture.h>
#include <mc/asset/art_logic.h>

namespace game
{
    class ArtLogicBlinnPhongPoint : public mc::asset::ArtLogic
    {

    private:
        static inline const std::string s_class_name{"game::art_logic::ArtLogicBlinnPhongPoint"};

    private:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        float m_shininess;
        const char *m_file_name;
        std::string m_m_name; // 材质名字

        std::shared_ptr<mc::asset::ShaderProgram> m_sp;
        std::shared_ptr<mc::asset::Texture> m_texture;

    private:
        static std::shared_ptr<ArtLogic> createFunc(const std::string &bin_data);

    public:
        ~ArtLogicBlinnPhongPoint() override;

    public:
        static void Register(mc::asset::ArtLogicFactory &af);

    public:
        // virtual
        void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) override;
        void SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> sp) override;
        void AddTexture(std::shared_ptr<mc::asset::Texture> texture) override;
        const std::string &ShowMe() override;
    };
}
#endif