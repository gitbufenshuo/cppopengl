#include <mc/material.h>
#include <mc/texture_store.h>
#include <mc/shader_store.h>
#include <mc/engine.h>

namespace game
{
    class MaterialPhongSpot : public mc::low::Material
    {
    public:
        using ShaderP = mc::low::ShaderP;
        using TextureP = mc::low::TextureP;
        using Engine = mc::low::Engine;
        using GameObject = mc::low::GameObject;
        struct SpotLight
        {
            glm::vec3 position;
            glm::vec3 direction{0.0f, 0.0f, -1.0f};
            float cutOff{0.976f};
            float outerCutOff{0.888f};

            float constant{1.0f};
            float linear{0.009f};
            float quadratic{0.0032f};

            glm::vec3 ambient{0.2f, 0.2f, 0.2f};
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

        ShaderP m_shader;
        TextureP m_texture;

    private:
        // 业务逻辑相关变量
        // 有的变量是绑在Engine上的，可以不用在这里定义，比如说 camera 相关
        // 具体这种变量在哪定义，按照业务逻辑来
        // 比如说下面的光源设置，本来应该定义在业务逻辑层，而不是这里
        // 当前写在这里是为了方便
        SpotLight m_spot_light; // 光源相关设置

    public:
        MaterialPhongSpot(const std::vector<float> &input, std::string_view name) : m_ambient{input[0], input[1], input[2]},
                                                                                    m_diffuse{input[3], input[4], input[5]},
                                                                                    m_specular{input[6], input[7], input[8]},
                                                                                    m_shininess{input[9] * 128.0f},
                                                                                    m_m_name{name}
        {
        }
        MaterialPhongSpot(const char *file_name);
        ~MaterialPhongSpot() override {}

    public:
        void PostUniform(Engine *eg, GameObject *gb) override;
        void SetShader(ShaderP shader) override;
        void AddTexture(TextureP texture) override;
    };

}