#include <iostream>
#include <vector>

#include <mc/engine.h>
#include <mc/gameobject.h>

#include <mc/model.h>
#include <mc/texture.h>
#include <mc/shader.h>

#include <mc/mesh_render.h>
#include <mc/material.h>
#include <mc/logic_support.h>

void show_hello();

using mlGB = mc::low::GameObject;
using mlModel = mc::low::Model;
using mlTexture = mc::low::Texture;
using mlShader = mc::low::Shader;
using mlRender = mc::low::MeshRender;
using mlFilter = mc::low::MeshFilter;
using mlMaterial = mc::low::Material;
using mlBasicLG = mc::low::BasicLogicSupport;
namespace
{
    std::vector<mlGB *> GenSome(mlRender *render, mlFilter *filter)
    {

        std::vector<mlGB *> res;
        int row = 11;
        int col = 11;
        res.resize(row * col);

        for (int row_idx = 0; row_idx < row; ++row_idx)
        {
            for (int col_idx = 0; col_idx < col; ++col_idx)
            {
                auto *one = new mlGB{};
                one->SetMeshFilter(filter);
                one->SetMeshRender(render);
                one->GetTransform()->SetLocalEuler(10.0f, 10.0f, 10.0f);
                one->GetTransform()->SetLocalTranslate(
                    static_cast<float>(col_idx) * 1.5f - 5.0f * 1.5f,
                    static_cast<float>(row_idx) * 1.5f - 5.0f * 1.5f,
                    -20.0f);
                one->AddLogicSupport(new mlBasicLG{one});
                res[row_idx * col + col_idx] = one;
            }
        }
        return res;
    }

    mlFilter *GetOneFilter()
    {
        auto *model_0{new mlModel{"../others/resource/model/cube.model"}};
        model_0->Upload();
        auto *filter_0{new mlFilter{}};
        filter_0->SetModel(model_0);
        return filter_0;
    }
    mlRender *GetOneRender()
    {
        auto *shader{new mlShader{"../others/resource/shader/phong.vert.vs", "../others/resource/shader/phong.frag.fs"}};
        shader->Load();

        auto *image{new mlTexture{"../others/resource/texture/mc.jpeg"}};
        image->Load();

        auto *_mate_emerald_material{new mlMaterial{"../others/resource/material/emerald.material"}};
        _mate_emerald_material->SetShader(shader);
        _mate_emerald_material->SetTexture(image);

        auto *render{new mlRender{}};
        render->SetMaterial(_mate_emerald_material);
        return render;
    }
}

int main()
{
    show_hello();
    //
    mc::low::Engine gogogo{800, 800, "Hello MC"};

    {
        auto list = GenSome(GetOneRender(), GetOneFilter());
        for (auto one : list)
        {
            // 这个里面所有的 gameobject 都是一个 filter 和 render
            gogogo.AddGameobject(one);
        }
    }

    gogogo.Run();
}
