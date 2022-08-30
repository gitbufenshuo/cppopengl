#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <mc/gameobject.h>
#include <mc/material.h>
#include <mc/tools_bound.h>

namespace mc::low
{
    class GameObject;
    class MeshRender
    {
        GameObject *m_gameobject;
        Bound m_bound;
        Material *m_material;
    };
}

#endif
