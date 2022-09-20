namespace mc::low
{
    class GameObject;
}

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>

#include <mc/transform.h>
#include <mc/mesh_render.h>
#include <mc/engine.h>

// asset
#include <mc/asset/act_logic.h>

namespace mc::low
{
    class MeshRender;
    class MeshFilter;
    class Engine;
    class GameObject
    {
        int m_id;
        std::string m_name;
        std::unique_ptr<Transform> m_transform;
        MeshRender *m_render;
        MeshFilter *m_filter;
        std::vector<std::shared_ptr<mc::asset::ActLogic>> act_list;
        Engine *m_engine;
        bool m_deleted{false}; // 是否已经被删除

    public:
        GameObject(Engine *m_engine = nullptr);
        ~GameObject();
        MeshRender *GetMeshRender();
        MeshFilter *GetMeshFilter();
        Transform *GetTransform();
        void SetMeshRender(MeshRender *mr);
        void SetMeshFilter(MeshFilter *mf);
        void SetID(int id);
        int GetID();
        void MarkDeleted();
        bool GetDeleted() const;
        void AddAct(std::shared_ptr<mc::asset::ActLogic> act);
        void Update(double delta_time);
        void BeforeRenderUpdate(double delta_time);
        void AfterRenderUpdate(double delta_time);
        Engine *GetEngine()
        {
            return m_engine;
        }
        void Destroy();
    };
}

#endif