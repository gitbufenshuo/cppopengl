#include <iostream>

#include <mc/gameobject.h>
#include <mc/engine.h>

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

    void GameObject::MarkDeleted()
    {
        m_deleted = true;
    }

    bool GameObject::GetDeleted() const
    {
        return m_deleted;
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
        return m_transform.get();
    }

    GameObject::GameObject(Engine *engine) : m_transform{std::make_unique<Transform>(this)}, m_engine{engine}
    {
    }
    GameObject::~GameObject()
    {
        delete m_render;
        delete m_filter;
        // std::cout << "~GameObject() " << m_id << std::endl;
    }

    void GameObject::SetID(int id)
    {
        m_id = id;
    }
    int GameObject::GetID()
    {
        return m_id;
    }
    void GameObject::AddAct(std::shared_ptr<mc::asset::ActLogic> act)
    {
        act_list.push_back(act);
    }
    void GameObject::Update(double delta_time)
    {
        for (auto one_act : act_list)
        {
            one_act->Update(delta_time);
        }
    }
    void GameObject::BeforeRenderUpdate(double delta_time, unsigned int layer)
    {
        for (auto one_act : act_list)
        {
            one_act->BeforeRenderUpdate(delta_time, layer);
        }
    }
    void GameObject::AfterRenderUpdate(double delta_time, unsigned int layer)
    {
        for (auto one_act : act_list)
        {
            one_act->AfterRenderUpdate(delta_time, layer);
        }
    }
    void GameObject::Destroy()
    {
        m_engine->DelGameobject(this);
    }

}