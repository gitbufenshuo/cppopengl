#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

#include <mc/transform.h>
#include <mc/mesh_render.h>

namespace mc::low
{
    class MeshRender;
    class GameObject
    {
        int m_id;
        std::string m_name;
        Transform *m_transform;
        MeshRender *m_render;

    public:
        MeshRender *GetMeshRender();
        Transform *GetTransform();
        void SetMeshRender(MeshRender *mr);
    };
}

#endif