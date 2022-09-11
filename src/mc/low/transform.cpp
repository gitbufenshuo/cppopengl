#include <iostream>

#include <glm/glm.hpp>

#include <mc/transform.h>

#include <mc/glmex/vec.h>

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

    void Transform::udpateAxis()
    {
        m_world_pos = m_world_mat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        m_world_x = m_world_mat * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        m_world_y = m_world_mat * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        m_world_z = m_world_mat * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }

    const glm::mat4 &Transform::GetWorldMat()
    {
        auto up_v = getUpperVersion();
        if (up_v != m_world_up_version)
        {
            m_world_mat = m_upper->GetWorldMat() * m_local_mat;
            m_world_up_version = up_v;
            ++m_world_self_version;
            udpateAxis();
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
    void Transform::SetLocalTranslate(float x, float y, float z)
    {
        m_local_dirty = true;
        //
        m_translate.x = x;
        m_translate.y = y;
        m_translate.z = z;
    }
    void Transform::IncLocalTranslate(float x, float y, float z)
    {
        m_local_dirty = true;
        //
        m_translate.x += x;
        m_translate.y += y;
        m_translate.z += z;
    }

    void Transform::SetLocalScale(float x, float y, float z)
    {
        m_local_dirty = true;
        //
        m_scale.x = x;
        m_scale.y = y;
        m_scale.z = z;
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
                udpateAxis();
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
    unsigned int Transform::GetSelfVersion()
    {
        return m_world_self_version;
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

    // void Transform::Rotate(){}
    // void Transform::Rotate(){}
    void showVec(const glm::vec3 &input)
    {
        std::cout << "        " << input.x << " "
                  << input.y << " "
                  << input.z << " "
                  << std::endl;
    }
    void showVec(const glm::vec4 &input)
    {
        std::cout << "        " << input.x << " "
                  << input.y << " "
                  << input.z << " "
                  << input.w << " "
                  << std::endl;
    }
    void showMat(const glm::mat4 &input)
    {
        std::cout << "---show mat---" << std::endl;
        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                std::cout << input[col][row] << " ";
            }
            std::cout << std::endl;
        }
    }
    glm::vec3 Transform::GetWorldPos()
    {
        GetWorldMat();
        return m_world_pos;
    }
    glm::vec3 Transform::GetWorldX()
    {
        GetWorldMat();
        return m_world_x;
    }
    glm::vec3 Transform::GetWorldY()
    {
        GetWorldMat();
        return m_world_y;
    }
    glm::vec3 Transform::GetWorldZ()
    {
        GetWorldMat();
        return m_world_z;
    }

    void Transform::Move(glm::vec3 diff, Space space)
    {
        GetWorldPos();
        glm::vec4 v_final;
        v_final.w = 1.0f;
        //
        if (space == Space::World)
        {
            v_final.x = m_world_pos.x + diff.x;
            v_final.y = m_world_pos.y + diff.y;
            v_final.z = m_world_pos.z + diff.z;
        }
        else
        {
            // diff 是相对于 local 来说的
            glm::vec3 lxdir{m_world_x - m_world_pos};
            glm::vec3 lydir{m_world_y - m_world_pos};
            glm::vec3 lzdir{m_world_z - m_world_pos};
            mc::glmex::AddInPlace(v_final, lxdir * diff.x);
            mc::glmex::AddInPlace(v_final, lydir * diff.y);
            mc::glmex::AddInPlace(v_final, lzdir * diff.z);
        }
        // 获得最终 v_final 之后
        // 先求 M_6 逆
        glm::mat4 m_6_inverse{1.0f}; // 单位阵
        if (m_upper)
        {
            // 有上级的情况下
            m_6_inverse = glm::inverse(m_upper->GetWorldMat());
        }
        auto equition_right{m_6_inverse * v_final};
        auto equition_left{GetLocalMat() * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
        IncLocalTranslate(equition_right.x - equition_left.x, equition_right.y - equition_left.y, equition_right.z - equition_left.z);
    }
}
