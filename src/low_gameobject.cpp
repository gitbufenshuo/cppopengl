#include <mc/gameobject.h>

namespace mc::low
{
    MeshRender *GameObject::GetMeshRender()
    {
        return m_render;
    }
    MeshFilter *GameObject::GetMeshFilter()
    {
        return m_filter;
    }

    void GameObject::SetMeshRender(MeshRender *mr)
    {
        m_render = mr;
    }
    void GameObject::SetMeshFilter(MeshFilter *mf)
    {
        m_filter = mf;
    }
    Transform *GameObject::GetTransform()
    {
        return m_transform;
    }

    GameObject::GameObject() : m_transform{new Transform{}}
    {
    }
    void GameObject::SetID(int id)
    {
        m_id = id;
    }
    int GameObject::GetID()
    {
        return m_id;
    }
    void GameObject::AddLogicSupport(LogicSupport *lg)
    {
        lg_list.push_back(lg);
    }
    void GameObject::Update(double delta_time)
    {
        for (auto onelg : lg_list)
        {
            onelg->Update(delta_time);
        }
    }
}