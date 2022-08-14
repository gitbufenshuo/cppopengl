#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
namespace mc::low
{
    class Transform
    {
    public:
        Transform();
        void SetUpper(Transform *upper);
        Transform &GetUpper() const;
        const glm::mat4 &GetMat() const;

    private:
        glm::vec3 m_scale{1.0f, 1.0f, 1.0f};
        glm::quat m_rotation{1.0f, 0.0f, 0.0f, 0.0f}; // 四元数
        glm::vec3 m_translate{0.0f, 0.0f, 0.0f};
        Transform *m_upper{nullptr};
        bool m_dirty{false};
        glm::mat4 m_model_mat{1.0f};
        //
    };
}

#endif