#include <iostream>
#include <vector>

#include <mc/engine.h>
#include <mc/gameobject.h>

#include <mc/model.h>
#include <mc/texture.h>
#include <mc/shader.h>

#include <mc/mesh_render.h>
#include <mc/material.h>
#include <mc/material_phong.h>
#include <mc/logic_support.h>

// game headers
#include <game/phong_spot.h>
//

using mlGB = mc::low::GameObject;
using mlModel = mc::low::Model;
using mlTexture = mc::low::Texture;
using mlShader = mc::low::Shader;
using mlRender = mc::low::MeshRender;
using mlFilter = mc::low::MeshFilter;
using mlMaterial = mc::low::Material;
using mlMaterialPhong = mc::low::MaterialPhong;
using mlBasicLG = mc::low::BasicLogicSupport;
using mlTranslateLG = mc::low::TranslateLogicSupport;
using mlCameraLG = mc::low::CameraLogicSupport;
namespace
{
    bool rangeshader(int key, mlShader *_shader)
    {
        std::cout << "rangeshader " << key << " " << _shader << std::endl;
        return true;
    }
    void LoadShader(mc::low::Engine &gogogo)
    {
        auto &shaderstore = gogogo.GetShaderStore();
        {
            // point phong
            auto *point_phong{new mlShader{"../others/resource/shader/phong.vert.vs", "../others/resource/shader/phong.frag.fs"}};
            point_phong->Load();
            shaderstore.Register(point_phong);
        }
        {
            // spot phong
            auto *spot_phong{new mlShader{"../others/resource/shader/phong.spot.vert.vs", "../others/resource/shader/phong.spot.frag.fs"}};
            spot_phong->Load();
            shaderstore.Register(spot_phong);
        }
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
        /*
            材质的概念：
            1. 包含材料本身的一些颜色性质，例如 diffuse，光滑度
            2. 包含这个材质用什么 shader 去 draw
            根据这个概念，那么 phong 光照模型下，使用 point light 和 spot light 属于两种材质
            当然可以合并这两个shader，本例只是用来展示自定义 shader 的写法，按道理来说，point light 和 spot light 两种 shader
            应该合并成一种 shader 里面。(learnopengl有示例)
        */

        // 加载phong材质，用point light
        // materialstore.LoadFromFile<mlMaterialPhong>("../others/resource/material/all.material", mlMaterial::MaterialType::PHONG);
        // 加载phong材质，用spot light
        materialstore.LoadFromFile<game::MaterialPhongSpot>("../others/resource/material/all.material", mlMaterial::MaterialType::PHONG_SPOT);
    }
    mlRender *GetOneRender(mc::low::Engine &gogogo, int gid)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        int mat_count = materialstore.GetCount();
        assert(mat_count);
        auto spMat{materialstore.Get(gid % mat_count)};
        spMat->SetShader(gogogo.GetShaderStore().Get(2)); // 这里用2号shader，就是spot phong
        spMat->AddTexture(gogogo.GetTextureStore().Get(1));

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
        std::cout << "resource load good" << std::endl;
        auto list = GenSome(gogogo, GetOneFilter(gogogo));
        std::cout << "Gen GameObject good" << std::endl;
        for (auto one : list)
        {
            // 这个里面所有的 gameobject 都是一个 filter 和 render
            gogogo.AddGameobject(one);
        }
    }
    std::cout << "gogogo.Run()" << std::endl;
    gogogo.Run();
}
