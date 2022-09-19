namespace mc::low
{
    class Transform;
}
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <mc/gameobject.h>
//
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
namespace mc::low
{
    enum class Space
    {
        World,
        Self
    };

    class Transform
    {
    public:
        // constructors;
        Transform(GameObject *gb = nullptr, float x = 0.0f, float y = 0.0f, float z = 0.0f);

    public:
        void SetUpper(Transform *upper);
        Transform &GetUpper() const;
        GameObject *GetGB() const;
        int SubSize();
        Transform *Sub(int index);
        const glm::mat4 &GetLocalMat();
        const glm::mat4 &GetWorldMat();
        glm::vec3 GetWorldPos();
        glm::vec3 GetWorldX();
        glm::vec3 GetWorldY();
        glm::vec3 GetWorldZ();
        void Translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void ShowVersion();
        unsigned int GetSelfVersion();
        void SetLocalEuler(float x, float y, float z);
        void IncLocalTranslate(float x, float y, float z);
        void SetLocalTranslate(float x, float y, float z);
        void SetLocalScale(float x, float y, float z);

        void Move(glm::vec3, Space = Space::Self);                                              // 移动
        void LookAt(Transform *target, const glm::vec3 &worldUp = glm::vec3{0.0f, 1.0f, 0.0f}); // 看向 target
        void SetLocalRotation(const glm::quat &local_rotation);                                 // 直接设置 local rotation
        void SetLocalRotation(float w, float x, float y, float z);                              // 直接设置 local rotation
        void Rotate(const glm::vec3 &axis, float angle, Space space = Space::Self);             // 绕 axis 轴 旋转 angle(°)
        void Rotate(float x, float y, float z, float angle, Space space = Space::Self);         // 绕 axis 轴 旋转 angle(°)

    private:
        void updateBranch();
        bool updateLocal();
        void udpateAxis();
        //
        GameObject *m_gb;
        glm::vec3 m_scale{1.0f, 1.0f, 1.0f};
        glm::quat m_rotation{1.0f, 0.0f, 0.0f, 0.0f}; // 四元数
        glm::vec3 m_translate{0.0f, 0.0f, 0.0f};
        glm::vec3 m_world_pos{0.0f};
        glm::vec3 m_world_z{0.0f};   // 世界坐标系下，transform 的 z
        glm::vec3 m_world_y{0.0f};   // 世界坐标系下，transform 的 y
        glm::vec3 m_world_x{0.0f};   // 世界坐标系下，transform 的 x
        Transform *m_upper{nullptr}; // 上层 transform
        bool m_local_dirty{false};   // local transform 是否有变化
        glm::mat4 m_local_mat{1.0f};
        glm::mat4 m_world_mat{1.0f};          // 这个能算出最后的世界坐标系中的坐标
        unsigned int m_world_up_version{0};   // 我使用的上一层的 world mat 版本
        unsigned int m_world_self_version{1}; // 我自己的 world mat 版本
        //
        std::vector<Transform *> m_sublist; // 我的一级子节点列表
    };
}

#endif