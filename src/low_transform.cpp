#include <iostream>

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
    void Transform::updateLocal()
    {
        if (!m_local_dirty)
        {
            return;
        }
        m_local_dirty = false;
        // local
        m_local_mat = glm::mat4(1.0f);
        m_local_mat = glm::translate(m_local_mat, m_translate);
        m_local_mat = m_local_mat * glm::toMat4(m_rotation);
        m_local_mat = glm::scale(m_local_mat, m_scale);
    }
    const glm::mat4 &Transform::GetLocalMat()
    {
        if (m_local_dirty)
        {
            updateLocal();
        }
        return m_local_mat;
    }
    const glm::mat4 &Transform::GetWorldMat()
    {
        auto up_v = getUpperVersion();
        if (up_v != m_world_up_version)
        {
            m_world_mat = m_upper->GetWorldMat() * m_local_mat;
            m_world_up_version = up_v;
            ++m_world_self_version;
        }
        return m_world_mat;
    }
    void Transform::Translate(float x, float y, float z)
    {
        m_local_dirty = true;
        //
        m_translate.x += x;
        m_translate.y += y;
        m_translate.z += z;
    }
    // 这个过程，会更新路径上所有节点的 local mat 和 world mat
    // 按需更新
    unsigned int Transform::getUpperVersion()
    {
        bool changed{false};
        // update local mat
        if (m_local_dirty)
        {
            updateLocal();
            changed = true;
        }
        //
        if (!m_upper)
        {
            if (changed)
            {
                m_world_mat = m_local_mat;
                ++m_world_self_version;
            }
            return 0;
        }
        //
        Transform &up_transform{*m_upper};
        auto uup = up_transform.getUpperVersion();
        if (uup != up_transform.m_world_up_version)
        {
            //
            Transform &up1_transform{*up_transform.m_upper};
            up_transform.m_world_mat = up1_transform.m_world_mat * up_transform.m_local_mat;
            up_transform.m_world_up_version = uup;
            ++up_transform.m_world_self_version;
        }
        //
        return up_transform.m_world_self_version;
    }
    void Transform::ShowVersion()
    {
        std::cout << m_world_self_version << " ";
        std::cout << m_world_up_version << std::endl;
    }
    void Transform::SetLocalEuler(float x, float y, float z)
    {
        auto cos_x_2 = glm::cos(glm::radians(x / 2.0f));
        auto sin_x_2 = glm::sin(glm::radians(x / 2.0f));

        auto cos_y_2 = glm::cos(glm::radians(y / 2.0f));
        auto sin_y_2 = glm::sin(glm::radians(y / 2.0f));

        auto cos_z_2 = glm::cos(glm::radians(z / 2.0f));
        auto sin_z_2 = glm::sin(glm::radians(z / 2.0f));

        glm::quat quat_x = glm::quat(cos_x_2, sin_x_2, 0, 0); // 绕 x 转 45
        glm::quat quat_y = glm::quat(cos_y_2, 0, sin_y_2, 0); // 绕 y 转 45
        glm::quat quat_z = glm::quat(cos_z_2, 0, 0, sin_z_2); // 绕 z 转 45
        auto quat_yx = glm::cross(quat_y, quat_x);            // y45 x45
        m_rotation = glm::cross(quat_z, quat_yx);             // z45 y45 x45
        m_local_dirty = true;
    }
}
