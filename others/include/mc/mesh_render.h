#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <mc/gameobject.h>
#include <mc/material.h>
#include <mc/model.h>
#include <mc/tools_bound.h>

namespace mc::low
{
    class GameObject;
    class MeshRender
    {
        GameObject *m_gameobject;
        Bound m_bound;
        Material *m_material;
        //
    public:
        MeshRender();
        void SetGameobject(GameObject *gameobject);
        void SetMaterial(Material *material);
        Material *GetMaterial()
        {
            return m_material;
        }
    };

    class MeshFilter
    {
        Model *m_model;

    public:
        void SetModel(Model *model)
        {
            m_model = model;
        }
        Model *GetModel()
        {
            return m_model;
        }
    };
}

#endif
