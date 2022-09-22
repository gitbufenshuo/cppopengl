#include <vector>
#include <mc/engine.h>

namespace
{
    std::vector<mc::low::GameObject *> g_outline_list;
}

namespace mc::low
{
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
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // 画普通的物体
        glStencilMask(0x00);

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
            if (_material->GetRenderBit(mc::asset::RENDER_LAYER_OUTLINE))
            {
                // 这是一个要画轮廓的玩意
                g_outline_list.push_back(_gb);
                continue;
            }
            auto _mesh_filter = _gb->GetMeshFilter();
            if (!_mesh_filter)
            {
                // 没有模型
                continue;
            }
            // material tasks
            auto art_logic{_material->GetArtLogic()};
            art_logic->PostUniform(this, _gb);
            _gb->BeforeRenderUpdate(delta_time);
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
            _gb->AfterRenderUpdate(delta_time);
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