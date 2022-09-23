#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <vector>
#include <memory>

#include <mc/gameobject.h>

// asset
#include <mc/asset/material.h>
#include <mc/asset/model.h>

namespace mc::low
{
    class GameObject;
    class MeshRender
    {
        GameObject *m_gameobject;
        std::shared_ptr<mc::asset::Material> m_material;
        //
    public:
        MeshRender();

    public:
        void SetGameobject(GameObject *gameobject);
        void SetMaterial(std::shared_ptr<mc::asset::Material> material);
        std::shared_ptr<mc::asset::Material> GetMaterial();
    };

    class MeshFilter
    {
        std::vector<std::shared_ptr<mc::asset::Model>> m_model_list;

    public:
        void AddModel(std::shared_ptr<mc::asset::Model> model)
        {
            m_model_list.push_back(model);
        }
        void SetModel(int index, std::shared_ptr<mc::asset::Model> model)
        {
            m_model_list[index] = model;
        }
        int modelsize()
        {
            return m_model_list.size();
        }
        std::shared_ptr<mc::asset::Model> GetModel(int index)
        {
            return m_model_list[index];
        }
    };
}

#endif
