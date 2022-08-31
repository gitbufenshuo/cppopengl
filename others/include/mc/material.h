#ifndef MC_LOW_MATERIAL_H
#define MC_LOW_MATERIAL_H

#include <vector>
#include <string>
#include <string_view>

#include <glm/glm.hpp>

#include <mc/texture_store.h>
#include <mc/shader_store.h>

namespace mc::low
{
    class Material
    {
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
        Material(const std::vector<float> &input, std::string_view name) : m_ambient{input[0], input[1], input[2]},
                                                                           m_diffuse{input[3], input[4], input[5]},
                                                                           m_specular{input[6], input[7], input[8]},
                                                                           m_shininess{input[9] * 128.0f},
                                                                           m_m_name{name}
        {
        }
        Material(const char *file_name);
        const glm::vec3 &GetAmbient() { return m_ambient; }
        const glm::vec3 &GetDiffuse() { return m_diffuse; }
        const glm::vec3 &GetSpecular() { return m_specular; }
        float GetShininess() { return m_shininess; }
        ShaderP GetShader()
        {
            return m_shader;
        }
        void SetShader(ShaderP shader)
        {
            m_shader = shader;
        }
        TextureP GetTexture()
        {
            return m_texture;
        }
        void SetTexture(TextureP texture)
        {
            m_texture = texture;
        }
    };
}
#endif