#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <vector>

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

    public:
        Bound GetBound()
        {
            return m_bound;
        }
        void SetGameobject(GameObject *gameobject);
        void SetMaterial(MaterialP material);
        MaterialP GetMaterial()
        {
            return m_material;
        }
    };

    class MeshFilter
    {
        std::vector<ModelP> m_model_list;

    public:
        void AddModel(ModelP model)
        {
            m_model_list.push_back(model);
        }
        int modelsize()
        {
            return m_model_list.size();
        }
        ModelP GetModel(int index)
        {
            return m_model_list[index];
        }
    };
}

#endif
