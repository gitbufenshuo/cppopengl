#ifndef MC_LOW_MATERIAL_H
#define MC_LOW_MATERIAL_H

#include <vector>
#include <glm/glm.hpp>

#include <mc/shader.h>

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
        Shader *m_shader;

    public:
        Material(const std::vector<float> &input) : m_ambient{input[0], input[1], input[2]},
                                                    m_diffuse{input[3], input[4], input[5]},
                                                    m_specular{input[6], input[7], input[8]},
                                                    m_shininess{input[9] * 128.0f}
        {
        }
        Material(const char *file_name);
        const glm::vec3 &GetAmbient() { return m_ambient; }
        const glm::vec3 &GetDiffuse() { return m_diffuse; }
        const glm::vec3 &GetSpecular() { return m_specular; }
        float GetShininess() { return m_shininess; }
        Shader *GetShader()
        {
            return m_shader;
        }
        void SetShader(Shader *shader)
        {
            m_shader = shader;
        }
    };
}
#endif