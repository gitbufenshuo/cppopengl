namespace mc::low
{
    class GameObject;
}

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include <mc/transform.h>
#include <mc/mesh_render.h>
#include <mc/logic_support.h>
#include <mc/engine.h>

namespace mc::low
{
    class MeshRender;
    class MeshFilter;
    class LogicSupport;
    class Engine;
    class GameObject
    {
        int m_id;
        std::string m_name;
        Transform *m_transform;
        MeshRender *m_render;
        MeshFilter *m_filter;
        std::vector<LogicSupport *> lg_list;
        Engine *m_engine;

    public:
        GameObject(Engine *m_engine = nullptr);
        MeshRender *GetMeshRender();
        MeshFilter *GetMeshFilter();
        Transform *GetTransform();
        void SetMeshRender(MeshRender *mr);
        void SetMeshFilter(MeshFilter *mf);
        void SetID(int id);
        int GetID();
        void AddLogicSupport(LogicSupport *lg);
        void Update(double delta_time);
        void BeforeRenderUpdate(double delta_time);
        void AfterRenderUpdate(double delta_time);
        Engine *GetEngine()
        {
            return m_engine;
        }
    };
}

#endif