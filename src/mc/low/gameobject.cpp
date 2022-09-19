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
    bool GameObject::GetDeleted()
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
        return m_transform;
    }

    GameObject::GameObject(Engine *engine) : m_transform{new Transform{this}}, m_engine{engine}
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
    void GameObject::BeforeRenderUpdate(double delta_time)
    {
        for (auto one_act : act_list)
        {
            one_act->BeforeRenderUpdate(delta_time);
        }
    }
    void GameObject::AfterRenderUpdate(double delta_time)
    {
        for (auto one_act : act_list)
        {
            one_act->AfterRenderUpdate(delta_time);
        }
    }

}