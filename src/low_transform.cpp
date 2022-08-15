#include <glm/gtc/matrix_transform.hpp>

#include <mc/transform.h>

namespace mc::low
{
    Transform::Transform()
    {
    }
    void Transform::SetUpper(Transform *upper)
    {
        m_upper = upper;
    }
    Transform &Transform::GetUpper() const
    {
        return *m_upper;
    }
    void Transform::updateMat()
    {
        if (!m_dirty)
        {
            return;
        }
        m_dirty = false;
        // local
        m_local_mat = glm::translate(m_local_mat, m_translate);
        m_local_mat = m_local_mat * glm::toMat4(m_rotation);
        m_local_mat = glm::scale(m_local_mat, m_scale);
        // world
        if (!m_upper)
        {
            m_world_mat = m_local_mat;
        }
        else
        {
            auto &upper_world = m_upper->GetWorldMat();
            m_world_mat = upper_world * m_local_mat;
        }
    }
    const glm::mat4 &Transform::GetLocalMat()
    {
        if (m_dirty)
        {
            updateMat();
        }
        return m_local_mat;
    }
    const glm::mat4 &Transform::GetWorldMat()
    {
        if (m_dirty)
        {
            updateMat();
        }
        return m_world_mat;
    }
    void Transform::Translate(float x, float y, float z)
    {
        m_dirty = true;
        //
        m_translate.x += x;
        m_translate.y += y;
        m_translate.z += z;
    }

}
