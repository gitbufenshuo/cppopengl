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
        const glm::mat4 &GetLocalMat();
        const glm::mat4 &GetWorldMat();

    private:
        void updateMat();
        //
        glm::vec3 m_scale{1.0f, 1.0f, 1.0f};
        glm::quat m_rotation{1.0f, 0.0f, 0.0f, 0.0f}; // 四元数
        glm::vec3 m_translate{0.0f, 0.0f, 0.0f};
        Transform *m_upper{nullptr};
        bool m_dirty{false}; // 下面两个矩阵是否需要更新
        glm::mat4 m_local_mat{1.0f};
        glm::mat4 m_world_mat{1.0f}; // 这个能算出最后的世界坐标系中的坐标
        //
    };
}

#endif