#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <mc/transform.h>

namespace mc::low
{
    class Camera
    {
    private:
        Transform m_transform{};
        float m_near{0.1f};
        float m_far{100.0f};
        float m_whr{1.0f};    // width / height
        float m_fov{45.0f};   // degree
        bool m_dirty{true};   // 是否需要更新 m_view_mat
        glm::mat4 m_view_mat; // view matrix
    };
}

#endif
