#ifndef LOGIC_SUPPORT_H
#define LOGIC_SUPPORT_H

#include <mc/gameobject.h>

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
    };

    class BasicLogicSupport : public LogicSupport
    {
        float sum_time{0.0f};

    public:
        BasicLogicSupport(GameObject *gb) : LogicSupport{gb}
        {
        }

    public:
        void Update(double delta_time) override;
    };

}
#endif