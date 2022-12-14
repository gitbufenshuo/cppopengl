#include <mc/mesh_render.h>

namespace mc::low
{
    MeshRender::MeshRender()
    {
    }
    void MeshRender::SetGameobject(GameObject *gameobject)
    {
        m_gameobject = gameobject;
    }
    void MeshRender::SetMaterial(std::shared_ptr<mc::asset::Material> material)
    {
        m_material = material;
    }
    std::shared_ptr<mc::asset::Material> MeshRender::GetMaterial()
    {
        return m_material;
    }
}