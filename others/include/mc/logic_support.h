#ifndef LOGIC_SUPPORT_H
#define LOGIC_SUPPORT_H

#include <glm/glm.hpp>

#include <mc/gameobject.h>
#include <mc/transform.h>

namespace mc::low
{
    class GameObject;

    class LogicSupport
    {
    protected:
        GameObject *m_gb;

    public:
        LogicSupport(GameObject *gb) : m_gb{gb} {}

    public:
        virtual void Update(double delta_time) = 0;
        virtual void RenderUpdate(double delta_time) = 0;
    };

    class BasicLogicSupport : public LogicSupport
    {
    protected:
        float sum_time{0.0f};
        float m_speed{0.0f};
        glm::vec3 m_init_pos;

    public:
        BasicLogicSupport(GameObject *gb = nullptr, float speed = 1.0f);

    public:
        void Update(double delta_time) override;
        void RenderUpdate(double delta_time) override;
    };

    class TranslateLogicSupport : public BasicLogicSupport
    {
    public:
        TranslateLogicSupport(GameObject *gb = nullptr, float speed = 1.0f) : BasicLogicSupport{gb, speed} {}

    public:
        void Update(double delta_time) override;
    };

    class CameraLogicSupport : public LogicSupport
    {
        Transform *m_camera_transform;
        float sum_time{0.0f};
        float m_speed{0.0f};

    public:
        CameraLogicSupport(GameObject *gb = nullptr, float speed = 1.0f);

    public:
        void Update(double delta_time) override;
        void RenderUpdate(double delta_time) override;
    };
}
#endif