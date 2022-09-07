#include <mc/engine.h>

namespace
{
    // 传 json 文件中 bufferViews 的下标
    unsigned int bufferViewUpload(const mc::gltf::GLTF &gltf, int index)
    {
        std::cout << "bufferViewUpload: " << index << std::endl;
        auto const &comm_gltf{gltf.GetCommGLTF()};
        auto &gltf_buffer_view{gltf.GetBufferView(index)};
        if (gltf_buffer_view.GetGLID() > 0)
        {
            return gltf_buffer_view.GetGLID();
        }
        auto &comm_buffer_view{comm_gltf.bufferviews(index)};
        auto &comm_buffer{comm_gltf.buffers(comm_buffer_view.buffer())};
        auto &gltf_buffer{gltf.GetBuffer(comm_buffer_view.buffer())};
        //
        unsigned int gl_buffer;
        glGenBuffers(1, &gl_buffer);
        glBindBuffer(comm_buffer_view.target(), gl_buffer);
        glBufferData(comm_buffer_view.target(), comm_buffer_view.bytelength(), gltf_buffer.Offset(comm_buffer_view.byteoffset()), GL_STATIC_DRAW);
        //
        auto &bv{const_cast<mc::gltf::BufferView &>(gltf_buffer_view)};
        bv.SetGLID(gl_buffer);
        return gl_buffer;
    }
}

namespace mc::low
{
    void Engine::LoadFromGLTF(const mc::gltf::GLTF &gltf)
    {
        auto const &comm_gltf{gltf.GetCommGLTF()};
        std::cout << "Engine::LoadFromGLTF gltf has " << comm_gltf.scenes_size() << " scenes" << std::endl;
        std::cout << "Engine::LoadFromGLTF loading default scene " << comm_gltf.scene() << std::endl;
        auto const &default_scene = comm_gltf.scenes(comm_gltf.scene());
        auto node_size = default_scene.nodes_size();
        for (int index = 0; index < node_size; ++index)
        {
            // 每一次循环创建一个gameobject
            std::cout << "Engine::LoadFromGLTF node " << index << " total: " << node_size << std::endl;
            auto node_index{default_scene.nodes(index)};
            auto &real_node{comm_gltf.nodes(node_index)};
            auto mesh_index{real_node.mesh()};
            auto &real_mesh{comm_gltf.meshes(mesh_index)};
            int pri_size = real_mesh.primitives_size();
            std::cout << "Engine::LoadFromGLTF pris " << pri_size << std::endl;
            unsigned int p_ebo, p_vbo, p_ebo_type;
            int p_ebo_size;
            auto n_gameobject{new GameObject{this}};
            auto n_mesh_filter{new MeshFilter{}};
            n_gameobject->SetMeshFilter(n_mesh_filter);
            for (int pindex = 0; pindex < pri_size; ++pindex)
            {
                // 每个 primitive 产生一个 mc::low::Model
                auto p_model{new Model{true}}; // 初始化vao并绑定vao
                auto &pri{real_mesh.primitives(pindex)};
                {
                    // 先考虑 ebo 的 accessor
                    auto &ebo_accessor{comm_gltf.accessors(pri.indices())};
                    p_ebo_size = ebo_accessor.count();
                    p_ebo_type = ebo_accessor.componenttype();
                    // 从 accessor 找到最终的 buffer，将 buffer 相应部分传到 gl
                    p_ebo = bufferViewUpload(gltf, ebo_accessor.bufferview());
                }
                {
                    // 开始搞 attributes
                    auto &attr{pri.attributes()};
                    {
                        // 顶点坐标
                        if (attr.position() > 0)
                        {
                            auto &acc{comm_gltf.accessors(attr.position())};
                            p_vbo = bufferViewUpload(gltf, acc.bufferview());
                            p_model->SetAttr(0, mc::gltf::Accessor::GetSizeFromType(acc.type()),
                                             comm_gltf.bufferviews(acc.bufferview()).bytestride(),
                                             (void *)(acc.byteoffset()));
                        }
                    }
                    {
                        // 法向量
                        if (attr.normal() > 0)
                        {
                            auto &acc{comm_gltf.accessors(attr.normal())};
                            bufferViewUpload(gltf, acc.bufferview());
                            p_model->SetAttr(1, mc::gltf::Accessor::GetSizeFromType(acc.type()),
                                             comm_gltf.bufferviews(acc.bufferview()).bytestride(),
                                             (void *)(acc.byteoffset()));
                        }
                    }
                    {
                        // 第一个贴图的uv
                        if (attr.texcoord_0() > 0)
                        {
                            auto &acc{comm_gltf.accessors(attr.texcoord_0())};
                            bufferViewUpload(gltf, acc.bufferview());
                            p_model->SetAttr(2, mc::gltf::Accessor::GetSizeFromType(acc.type()),
                                             comm_gltf.bufferviews(acc.bufferview()).bytestride(),
                                             (void *)(acc.byteoffset()));
                        }
                    }
                }
                p_model->SetGLID(p_vbo, p_ebo, p_ebo_type, p_ebo_size);
                m_model_store.Register(p_model);
                n_mesh_filter->AddModel(m_model_store.Get()); // 获取最后一个
            }
            // mesh render 暂时
            auto mr{new MeshRender{}};
            mr->SetMaterial(m_material_store.Get());
            n_gameobject->SetMeshRender(mr);
            n_gameobject->GetTransform()->SetLocalTranslate(0.0f, 0.0f, -5.0f);
            n_gameobject->GetTransform()->SetLocalEuler(0.0f, 0.0f, 0.0f);
            this->AddGameobject(n_gameobject);
        }
    }
}