#include <iostream>
#include <vector>
#include <string>

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
#include <game/example/example_list.h>
#include <game/logic/camera_logic.h>
#include <game/logic/rotate_logic.h>
#include <game/logic/lookat_logic.h>
#include <game/logic/translate_logic.h>

// comm headers

using mlGB = mc::low::GameObject;
using mlModel = mc::low::Model;
using mlTexture = mc::low::Texture;
using mlShader = mc::low::Shader;
using mlRender = mc::low::MeshRender;
using mlFilter = mc::low::MeshFilter;
using mlMaterial = mc::low::Material;
using mlMaterialPhong = mc::low::MaterialPhong;
namespace
{
    void LoadShader(mc::low::Engine &gogogo)
    {
        auto &shaderstore = gogogo.GetShaderStore();
        {
            // point phong
            auto *point_phong{new mlShader{"../others/resource/shader/phong.vert.vs", "../others/resource/shader/phong.frag.fs"}};
            point_phong->Load();
            shaderstore.Register(point_phong);
        }
    }
    void LoadModel(mc::low::Engine &gogogo)
    {
        auto &modelstore = gogogo.GetModelStore();
        {
            // load from file
            auto *model_0{new mlModel{"../others/resource/model/cube.model", true}};
            model_0->Upload();
            modelstore.Register(model_0);
        }
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
        {
            // 加载 phong 材质， point light
            auto list = mlMaterialPhong::LoadSurfaceDataFromFile("../others/resource/material/all.material");
            // 注册到 engine 中
            for (auto one : list)
            {
                one->SetShader(gogogo.GetShaderStore().Get(1)); // 设置一下关联的shader 1
                one->AddTexture(gogogo.GetTextureStore().Get(1));
                materialstore.Register(one);
            }
        }
    }
    mlRender *GetOneRender(mc::low::Engine &gogogo, int id)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        auto spMat{materialstore.Get(id + 1)}; //   mat_count/2 + 1 是spot phong
        auto *render{new mlRender{}};
        render->SetMaterial(spMat);
        return render;
    };

    mlFilter *GetOneFilter(mc::low::Engine &gogogo);

    std::vector<mlGB *> GenSomeGameobject(mc::low::Engine &gogogo)
    {
        std::vector<mlGB *> res;
        int gb_size = 3;
        res.resize(gb_size);

        // root transform
        {
            auto *one = new mlGB{&gogogo};
            one->SetMeshFilter(GetOneFilter(gogogo));
            one->SetMeshRender(GetOneRender(gogogo, 0));
            one->GetTransform()->SetLocalTranslate(0.0f, -10.0f, -20.0f);
            one->AddLogicSupport(new game::RotateLogic{one});
            res[0] = one;
        }
        {
            auto *one = new mlGB{&gogogo};
            one->SetMeshFilter(GetOneFilter(gogogo));
            one->SetMeshRender(GetOneRender(gogogo, 1));
            one->GetTransform()->SetUpper(res[0]->GetTransform());
            one->GetTransform()->SetLocalTranslate(5.0f, 0.0f, 0.0f);
            one->AddLogicSupport(new game::TranslateLogic{one});
            res[1] = one;
        }
        {
            auto *one = new mlGB{&gogogo};
            one->SetMeshFilter(GetOneFilter(gogogo));
            one->SetMeshRender(GetOneRender(gogogo, 2));
            one->GetTransform()->SetUpper(res[0]->GetTransform());
            one->GetTransform()->SetLocalTranslate(2.0f, 2.0f, 0.0f);
            one->AddLogicSupport(new game::LookatLogic{one, res[1]->GetTransform()});
            res[2] = one;
        }
        res[1]->AddLogicSupport(new game::LookatLogic{res[1], res[2]->GetTransform()});
        return res;
    }

    mlFilter *GetOneFilter(mc::low::Engine &gogogo)
    {
        auto &modelstore{gogogo.GetModelStore()};
        auto *filter_0{new mlFilter{}};
        filter_0->AddModel(modelstore.Get(1));
        return filter_0;
    }

}

namespace game::example_list::cube_transform
{
    int Main()
    {
        //
        mc::low::Engine gogogo{800, 800, "Hello MC"};
        {
            LoadShader(gogogo);
            LoadModel(gogogo);
            LoadTexture(gogogo);
            LoadMaterial(gogogo);
            std::cout << "resource load good" << std::endl;
            auto list = GenSomeGameobject(gogogo);
            std::cout << "Gen GameObject good" << std::endl;
            for (auto one : list)
            {
                // 这个里面所有的 gameobject 都是一个 filter 和 render
                gogogo.AddGameobject(one);
            }
        }
        std::cout << "gogogo.Run()" << std::endl;
        auto camera = gogogo.GetCamera();
        camera->GetTransform()->SetLocalTranslate(0.0f, 0.0f, 20.0f);
        gogogo.Run();
        return 0;
    }

}
