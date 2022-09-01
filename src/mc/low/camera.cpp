#include <mc/camera.h>
namespace mc::low
{
    Camera::Camera()
    {
    }
    void Camera::updateViewMat()
    {
        auto camera_world_mat = m_transform.GetWorldMat();
        if (m_camera_version == m_transform.GetSelfVersion())
        {
            return;
        }
        m_camera_version = m_transform.GetSelfVersion();

        glm::vec4 _pos{0.0f, 0.0f, 0.0f, 1.0f};
        glm::vec4 _target{0.0f, 0.0f, -1.0f, 1.0f};
        glm::vec4 _up{0.0f, 1.0f, 0.0f, 1.0f};

        _pos = camera_world_mat * _pos;
        _target = camera_world_mat * _target;

        m_view_mat = glm::lookAt(glm::vec3(_pos.x, _pos.y, _pos.z),
                                 glm::vec3(_target.x, _target.y, _target.z),
                                 glm::vec3(_up.x, _up.y, _up.z));
    }

    const glm::mat4 &Camera::GetViewMat()
    {
        if (m_view_dirty)
        {
            updateViewMat();
        }
        return m_view_mat;
    }

    void Camera::updateProjMat()
    {
        if (!m_proj_dirty)
        {
            return;
        }
        m_proj_dirty = false;
        //
        m_proj_mat = glm::perspective(glm::radians(m_fov), m_whr, m_near, m_far);
    }
    const glm::mat4 &Camera::GetProjMat()
    {
        if (m_proj_dirty)
        {
            updateProjMat();
        }
        return m_proj_mat;
    }
    Transform *Camera::GetTransform()
    {
        return &m_transform;
    }

}