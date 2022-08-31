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
    void MeshRender::SetMaterial(MaterialP material)
    {
        m_material = material;
    }

}