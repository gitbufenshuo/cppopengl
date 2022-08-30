#include <mc/gameobject.h>

namespace mc::low
{
    MeshRender *GameObject::GetMeshRender()
    {
        return m_render;
    }
    void GameObject::SetMeshRender(MeshRender *mr)
    {
        m_render = mr;
    }
    Transform *GameObject::GetTransform()
    {
        return m_transform;
    }

}