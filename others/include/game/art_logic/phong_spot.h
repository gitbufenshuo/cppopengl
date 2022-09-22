#ifndef GAME_PHONG_SPOT_H
#define GAME_PHONG_SPOT_H
#include <string>
#include <mc/engine.h>

#include <mc/asset/art_logic.h>

namespace game
{
    class ArtLogicPhongSpot : public mc::asset::ArtLogic
    {
    public:
        struct SpotLight
        {
            glm::vec3 position;
            glm::vec3 direction{0.0f, 0.0f, -1.0f};
            float cutOff{0.999f};
            float outerCutOff{0.9f};

            float constant{1.0f};
            float linear{0.009f};
            float quadratic{0.0032f};

            glm::vec3 ambient{0.1f, 0.1f, 0.1f};
            glm::vec3 diffuse{1.0f, 1.0f, 1.0f};
            glm::vec3 specular{0.1f, 0.1f, 0.1f};
        };

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
        // 业务逻辑相关变量
        // 有的变量是绑在Engine上的，可以不用在这里定义，比如说 camera 相关
        // 具体这种变量在哪定义，按照业务逻辑来
        // 比如说下面的光源设置，本来应该定义在业务逻辑层，而不是这里
        // 当前写在这里是为了方便
        SpotLight m_spot_light; // 光源相关设置

        ///////////////////
    private:
        static std::shared_ptr<ArtLogic> createFunc(const std::string &bin_data);
        static inline const std::string s_class_name{"game::art_logic::ArtLogicPhongSpot"};

    public:
        ~ArtLogicPhongSpot() override;

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