#include <vector>
#include <mc/engine.h>

namespace
{
    std::vector<mc::low::GameObject *> g_plain_list;       // 普通的
    std::vector<mc::low::GameObject *> g_outline_list;     // 需要画 outline 的
    std::vector<mc::low::GameObject *> g_shadow_cast_list; // 会发出阴影的
}

namespace mc::low
{
    /**
     * @brief 生成 shadow map
     *
     */
    void Engine::shadow_generate()
    {
        glCullFace(GL_FRONT);
        // 遍历每一个 light, 将 depth 渲染到对应的 texture
        for (auto one_light : m_light_list)
        {
            glViewport(0, 0, one_light->GetShadowWidth(), one_light->GetShadowHeight());
            glBindFramebuffer(GL_FRAMEBUFFER, one_light->GetShadowFBO());
            glClear(GL_DEPTH_BUFFER_BIT);
            one_light->CalcLightMat();
            auto art_logic{one_light->GetArtLogic()};
            for (auto one_gb : g_shadow_cast_list)
            {
                art_logic->PostUniform(this, one_gb);
                auto _mesh_filter{one_gb->GetMeshFilter()};
                int model_size = _mesh_filter->modelsize();
                for (int index = 0; index < model_size; ++index)
                {
                    auto _model = _mesh_filter->GetModel(index);
                    _model->Use();
                    glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), _model->GetEBOType(), 0);
                }
            }
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glCullFace(GL_BACK);
        g_shadow_cast_list.resize(0);
    }
    void Engine::draw_plain()
    {
        glViewport(0, 0, m_width, m_height);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0x00);
        for (auto one_gb : g_plain_list)
        {
            auto mr = one_gb->GetMeshRender();
            auto _material = mr->GetMaterial();
            auto _mesh_filter = one_gb->GetMeshFilter();
            // material tasks
            auto art_logic{_material->GetArtLogic()};
            art_logic->PostUniform(this, one_gb);
            one_gb->BeforeRenderUpdate(delta_time);
            // 遍历每一个 primitive model
            {
                int model_size = _mesh_filter->modelsize();
                for (int index = 0; index < model_size; ++index)
                {
                    auto _model = _mesh_filter->GetModel(index);
                    _model->Use();
                    glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), _model->GetEBOType(), 0);
                }
            }
            one_gb->AfterRenderUpdate(delta_time);
        }
        g_plain_list.resize(0);
    }

    void Engine::outline_render()
    {
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        for (auto one_gb : g_outline_list)
        {
            auto mr = one_gb->GetMeshRender();
            if (!mr)
            {
                // 没有 mesh render, 相当于不用渲染
                continue;
            }
            auto _material = mr->GetMaterial();
            if (!_material)
            {
                // 没有 材质，说明这个mesh render 设置不完整
                continue;
            }
            auto _mesh_filter = one_gb->GetMeshFilter();
            if (!_mesh_filter)
            {
                // 没有模型
                continue;
            }
            // material tasks
            auto art_logic{_material->GetArtLogic()};
            one_gb->BeforeRenderUpdate(delta_time);
            art_logic->PostUniform(this, one_gb);
            // 遍历每一个 primitive model
            {
                int model_size = _mesh_filter->modelsize();
                for (int index = 0; index < model_size; ++index)
                {
                    auto _model = _mesh_filter->GetModel(index);
                    _model->Use();
                    glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), _model->GetEBOType(), 0);
                }
            }
            one_gb->AfterRenderUpdate(delta_time);
        }
        //
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0xFF);
        glDisable(GL_DEPTH_TEST);
        //
        for (auto one_gb : g_outline_list)
        {
            auto mr = one_gb->GetMeshRender();
            if (!mr)
            {
                // 没有 mesh render, 相当于不用渲染
                continue;
            }
            auto _material = mr->GetMaterial();
            if (!_material)
            {
                // 没有 材质，说明这个mesh render 设置不完整
                continue;
            }
            auto _mesh_filter = one_gb->GetMeshFilter();
            if (!_mesh_filter)
            {
                // 没有模型
                continue;
            }
            // material tasks
            auto art_logic{_material->GetArtLogic()};
            one_gb->BeforeRenderUpdate(delta_time, mc::asset::RENDER_LAYER_OUTLINE);
            art_logic->PostUniform(this, one_gb);
            // 遍历每一个 primitive model
            {
                int model_size = _mesh_filter->modelsize();
                for (int index = 0; index < model_size; ++index)
                {
                    auto _model = _mesh_filter->GetModel(index);
                    _model->Use();
                    glDrawElements(GL_TRIANGLES, _model->GetEBOCount(), _model->GetEBOType(), 0);
                }
            }
            one_gb->AfterRenderUpdate(delta_time, mc::asset::RENDER_LAYER_OUTLINE);
        }
        g_outline_list.resize(0);
        //
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
    }

    void Engine::standard_render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // 遍历各个 gameobject, 画出来
        for (auto &pair : m_gameobjects)
        {
            auto _gb = pair.second.get();
            auto mr = pair.second->GetMeshRender();
            if (!mr)
            {
                // 没有 mesh render, 相当于不用渲染
                continue;
            }
            auto _material = mr->GetMaterial();
            if (!_material)
            {
                // 没有 材质，说明这个mesh render 设置不完整
                continue;
            }
            auto b_outline{_material->GetRenderBit(mc::asset::RENDER_LAYER_OUTLINE)};
            auto b_cast_shadow{_material->GetCastShadow()};
            if (b_outline || b_cast_shadow)
            {
                if (b_outline)
                {
                    g_outline_list.push_back(_gb);
                }
                if (b_cast_shadow)
                {
                    g_shadow_cast_list.push_back(_gb);
                    g_plain_list.push_back(_gb);
                }
            }
            else
            {
                g_plain_list.push_back(_gb);
            }
        }
    }

    void Engine::draw_skybox()
    {
        // draw skybox
        glDepthFunc(GL_LEQUAL);
        m_main_camera->DrawSkybox();
        glDepthFunc(GL_LESS);
    }

}