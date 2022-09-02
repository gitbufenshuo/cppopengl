
#include <mc/material.h>
#include <mc/texture_store.h>
#include <mc/shader_store.h>
#include <mc/engine.h>

namespace game
{
    class MaterialBlinnPhongPoint : public mc::low::Material
    {
    public:
        using ShaderP = mc::low::ShaderP;
        using TextureP = mc::low::TextureP;
        using Engine = mc::low::Engine;
        using GameObject = mc::low::GameObject;
    private:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        float m_shininess;
        const char *m_file_name;
        std::string m_m_name; // 材质名字

        ShaderP m_shader;
        TextureP m_texture;

    public:
        MaterialBlinnPhongPoint(const std::vector<float> &input, std::string_view name) : m_ambient{input[0], input[1], input[2]},
                                                                                m_diffuse{input[3], input[4], input[5]},
                                                                                m_specular{input[6], input[7], input[8]},
                                                                                m_shininess{input[9] * 128.0f},
                                                                                m_m_name{name}
        {
        }
        MaterialBlinnPhongPoint(const char *file_name);
        ~MaterialBlinnPhongPoint() override {}

    public:
        static std::vector<Material *> LoadSurfaceDataFromFile(const char *filename);

    public:
        // virtual
        void PostUniform(Engine *eg, GameObject *gb) override;
        void SetShader(ShaderP shader) override;
        void AddTexture(TextureP texture) override;
    };
}