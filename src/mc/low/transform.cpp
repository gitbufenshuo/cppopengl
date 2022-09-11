#include <iostream>
#include <vector>

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
    bool Transform::updateLocal()
    {
        if (!m_local_dirty)
        {
            return false; // 本地无变化
        }
        m_local_dirty = false;
        // local
        m_local_mat = glm::mat4(1.0f);
        m_local_mat = glm::translate(m_local_mat, m_translate);
        m_local_mat = m_local_mat * glm::toMat4(m_rotation);
        m_local_mat = glm::scale(m_local_mat, m_scale);
        return true;
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
        updateBranch();
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
        // std::cout << " Transform::IncLocalTranslate " << x << " " << y << " " << z << std::endl;
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

    // 更新本transform至root节点，所有transform的状态
    void Transform::updateBranch()
    {
        static unsigned int func_counter{0};
        ++func_counter;
        std::vector<Transform *> all_list;
        all_list.reserve(10); // 大概预设一个大小，省的不停的 malloc,free
        auto now_t{this};
        while (now_t)
        {
            all_list.push_back(now_t);
            // std::cout << " Transform::updateBranch append " << func_counter << " " << now_t << std::endl;
            now_t = &(now_t->GetUpper());
        }

        // 逆向遍历, 从root开始
        int size = static_cast<int>(all_list.size());
        bool local_changed{false};
        bool up_changed{false};
        for (int index = size - 1; index >= 0; --index)
        {
            now_t = all_list[index];
            // 更新自身的变化
            local_changed = now_t->updateLocal();
            if (now_t->m_upper)
            {
                // 如果有 上级
                if (now_t->m_world_up_version != now_t->m_upper->m_world_self_version)
                {
                    // 如果上级变了
                    up_changed = true;
                    m_world_up_version = now_t->m_upper->m_world_self_version;
                    m_world_mat = now_t->m_upper->m_world_mat * m_local_mat;
                }
                else
                {
                    // 如果上级没变
                    up_changed = false;
                    if (local_changed)
                    {
                        m_world_mat = now_t->m_upper->m_world_mat * m_local_mat;
                    }
                }
            }
            else
            {
                // 没有上级 (这就是root)
                up_changed = false;
                now_t->m_world_mat = now_t->m_local_mat;
            }
            if (local_changed || up_changed)
            {
                // 到此时，local 矩阵 和 world 矩阵都已经更新完毕
                // 只要有变化，那么本身的版本号就要++
                // std::cout << this << " " << func_counter << " before debug transform update " << now_t->m_world_self_version << std::endl;
                ++now_t->m_world_self_version;
                // std::cout << this << " " << func_counter << " debug transform update " << now_t->m_world_self_version << std::endl;
                //  更新一些属性(四个坐标点)
                now_t->udpateAxis();
            }
        }
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
    void showMat(const glm::mat4 &input, const char *info = "")
    {
        std::cout << "---show mat---" << info << std::endl;
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
        updateBranch();
        return m_world_pos;
    }
    glm::vec3 Transform::GetWorldX()
    {
        updateBranch();
        return m_world_x;
    }
    glm::vec3 Transform::GetWorldY()
    {
        updateBranch();
        return m_world_y;
    }
    glm::vec3 Transform::GetWorldZ()
    {
        updateBranch();
        return m_world_z;
    }

    void Transform::Move(glm::vec3 diff, Space space)
    {
        updateBranch();
        glm::vec4 v_final;
        v_final.x = m_world_pos.x;
        v_final.y = m_world_pos.y;
        v_final.z = m_world_pos.z;
        v_final.w = 1.0f;
        //
        if (space == Space::World)
        {
            v_final.x += diff.x;
            v_final.y += diff.y;
            v_final.z += diff.z;
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
        auto equition_left{m_local_mat * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
        IncLocalTranslate(equition_right.x - equition_left.x, equition_right.y - equition_left.y, equition_right.z - equition_left.z);
    }

    /*
        修改 local m_rotation，使得本 transform 最终
        1. 本transform 的 y轴 指向 worldUp
        2. 本transform 的 z轴 指向 target
    */
    void Transform::LookAt(Transform *target, const glm::vec3 &worldUp)
    {
        updateBranch();
        const glm::vec3 &target_pos{target->GetWorldPos()};
        const glm::vec3 &now_origin{m_world_pos};
        // 先计算 最终的 world_x world_y world_z
        auto z_dir = glm::normalize(target_pos - now_origin);
        auto final_z = z_dir + now_origin;
        auto x_dir = glm::normalize(glm::cross(worldUp, z_dir));
        auto y_dir = glm::cross(z_dir, x_dir);
        auto final_x = x_dir + now_origin;
        auto final_y = y_dir + now_origin;
        // 求 m6_inverse
        glm::mat4 m6;
        if (m_upper)
        {
            // 有上级
            m6 = m_upper->GetWorldMat();
        }
        else
        {
            // 没有上级
            m6 = m_upper->GetWorldMat();
        }
        glm::mat4 localT{1.0f};
        localT[3][0] = m_translate.x;
        localT[3][1] = m_translate.y;
        localT[3][2] = m_translate.z;
        localT[3][3] = 1.0f;
        m6 = m6 * localT;
        m6 = glm::inverse(m6);
        // 得到最终的 local 旋转矩阵 放到 m6 中
        auto col0 = m6 * glm::vec4{final_x.x, final_x.y, final_x.z, 1.0f};
        auto col1 = m6 * glm::vec4{final_y.x, final_y.y, final_y.z, 1.0f};
        auto col2 = m6 * glm::vec4{final_z.x, final_z.y, final_z.z, 1.0f};
        m6[0][0] = col0.x / m_scale.x;
        m6[0][1] = col0.y / m_scale.x;
        m6[0][2] = col0.z / m_scale.x;
        m6[0][3] = 0.0f;

        m6[1][0] = col1.x / m_scale.y;
        m6[1][1] = col1.y / m_scale.y;
        m6[1][2] = col1.z / m_scale.y;
        m6[1][3] = 0.0f;

        m6[2][0] = col2.x / m_scale.z;
        m6[2][1] = col2.y / m_scale.z;
        m6[2][2] = col2.z / m_scale.z;
        m6[2][3] = 0.0f;

        m6[3][0] = 0.0f;
        m6[3][1] = 0.0f;
        m6[3][2] = 0.0f;
        m6[3][3] = 1.0f;
        // 利用最终的 local 旋转矩阵反推 最终的 local quaternion

        auto calc_rotation{glm::toQuat(m6)};
        m_rotation = glm::slerp(m_rotation, calc_rotation, 1.0f);
        // std::cout << " m_rotation.w " << m_rotation.w << " "
        //           << " m_rotation.x " << m_rotation.x << " "
        //           << " m_rotation.y " << m_rotation.y << " "
        //           << " m_rotation.z " << m_rotation.z << " " << std::endl;
        m_local_dirty = true;
    }

}
