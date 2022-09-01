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

using mlGB = mc::low::GameObject;
using mlModel = mc::low::Model;
using mlTexture = mc::low::Texture;
using mlShader = mc::low::Shader;
using mlRender = mc::low::MeshRender;
using mlFilter = mc::low::MeshFilter;
using mlMaterial = mc::low::Material;
using mlBasicLG = mc::low::BasicLogicSupport;
using mlTranslateLG = mc::low::TranslateLogicSupport;
using mlCameraLG = mc::low::CameraLogicSupport;
namespace
{
    bool rangeshader(int key, mlShader *_shader)
    {
        std::cout << key << " " << _shader << std::endl;
        return true;
    }
    void LoadShader(mc::low::Engine &gogogo)
    {
        auto *shader{new mlShader{"../others/resource/shader/phong.vert.vs", "../others/resource/shader/phong.frag.fs"}};
        shader->Load();
        auto &shaderstore = gogogo.GetShaderStore();
        shaderstore.Register(shader);
        //
        shaderstore.Range(rangeshader);
    }
    void LoadModel(mc::low::Engine &gogogo)
    {
        auto *model_0{new mlModel{"../others/resource/model/cube.model"}};
        model_0->Upload();
        auto &modelstore = gogogo.GetModelStore();
        modelstore.Register(model_0);
    }
    void LoadTexture(mc::low::Engine &gogogo)
    {
        auto *image{new mlTexture{"../others/resource/texture/mc.jpeg"}};
        image->Load();
        auto &textruestore{gogogo.GetTextureStore()};
        textruestore.Register(image);
    }
    void LoadMaterial(mc::low::Engine &gogogo)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        materialstore.LoadFromFile("../others/resource/material/all.material");
    }
    mlRender *GetOneRender(mc::low::Engine &gogogo, int gid)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        int mat_count = materialstore.GetCount();
        auto spMat{materialstore.Get(gid % mat_count)};

        spMat->SetShader(gogogo.GetShaderStore().Get(1));
        spMat->SetTexture(gogogo.GetTextureStore().Get(1));

        auto *render{new mlRender{}};
        render->SetMaterial(spMat);
        return render;
    }
    std::vector<mlGB *> GenSome(mc::low::Engine &gogogo, mlFilter *filter)
    {
        std::vector<mlGB *> res;
        int row = 11;
        int col = 11;
        res.resize(row * col);

        for (int row_idx = 0; row_idx < row; ++row_idx)
        {
            for (int col_idx = 0; col_idx < col; ++col_idx)
            {
                auto *one = new mlGB{&gogogo};
                one->SetMeshFilter(filter);
                one->SetMeshRender(GetOneRender(gogogo, col_idx + row_idx * col));
                one->GetTransform()->SetLocalEuler(10.0f, 10.0f, 10.0f);
                one->GetTransform()->SetLocalTranslate(
                    static_cast<float>(col_idx) * 1.5f - 5.0f * 1.5f,
                    static_cast<float>(row_idx) * 1.5f - 5.0f * 1.5f,
                    -20.0f);
                one->AddLogicSupport(new mlCameraLG{one, 1.5f});
                res[row_idx * col + col_idx] = one;
            }
        }
        return res;
    }

    mlFilter *GetOneFilter(mc::low::Engine &gogogo)
    {
        auto &modelstore{gogogo.GetModelStore()};
        auto *filter_0{new mlFilter{}};
        filter_0->SetModel(modelstore.Get(1));
        return filter_0;
    }

}

int main()
{
    //
    mc::low::Engine gogogo{800, 800, "Hello MC"};
    {
        LoadShader(gogogo);
        LoadModel(gogogo);
        LoadTexture(gogogo);
        LoadMaterial(gogogo);
        auto list = GenSome(gogogo, GetOneFilter(gogogo));
        for (auto one : list)
        {
            // 这个里面所有的 gameobject 都是一个 filter 和 render
            gogogo.AddGameobject(one);
        }
    }

    gogogo.Run();
}
