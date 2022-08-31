#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <mc/gameobject.h>
#include <mc/material.h>
#include <mc/model_store.h>
#include <mc/material_store.h>
#include <mc/tools_bound.h>

namespace mc::low
{
    class GameObject;
    class MeshRender
    {
        GameObject *m_gameobject;
        Bound m_bound;
        MaterialP m_material;
        //
    public:
        MeshRender();
        void SetGameobject(GameObject *gameobject);
        void SetMaterial(MaterialP material);
        MaterialP GetMaterial()
        {
            return m_material;
        }
    };

    class MeshFilter
    {
        ModelP m_model;

    public:
        void SetModel(ModelP model)
        {
            m_model = model;
        }
        ModelP GetModel()
        {
            return m_model;
        }
    };
}

#endif
