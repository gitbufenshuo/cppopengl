#include <iostream>
#include <string>
#include <fstream>
// mc low headers
#include <mc/engine.h>
#include <mc/material_phong.h>

// game headers

// comm headers
#include <mc/comm/gltf.pb.h>
#include <mc/gltf/buffer.h>

using mlShader = mc::low::Shader;
using mlMaterialPhong = mc::low::MaterialPhong;

namespace
{

    void loadAndParse(mc::comm::GLTF &gltf)
    {
        {
            std::ifstream file_stream("../others/resource/gltf/minimal.json.gltf.pb", std::ios::in | std::ios::binary);
            auto ok{gltf.ParseFromIstream(&file_stream)};
            if (!ok)
            {
                std::cout << "loading gltf.pb fail" << std::endl;
            }
        }
        mc::gltf::BufferList buffers{gltf};
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
    }

    void LoadMaterial(mc::low::Engine &gogogo)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        {
            // 加载 phong 材质， point light
            auto list = mlMaterialPhong::LoadSurfaceDataFromFile("../others/resource/material/all.material");
            // 注册到 engine 中
            for (auto one : list)
            {
                one->SetShader(gogogo.GetShaderStore().Get(1)); // 设置一下关联的shader 1
                // one->AddTexture(gogogo.GetTextureStore().Get(1));
                materialstore.Register(one);
            }
        }
    }

}

namespace game::example_list::gltf_exp
{
    int Main()
    {
        mc::comm::GLTF gltf;
        loadAndParse(gltf);
        mc::low::Engine gogogo{800, 800, "Hello GLTF EXP"};
        LoadShader(gogogo);
        LoadMaterial(gogogo);
        gogogo.LoadFromGLTF(gltf);
        gogogo.Run();
        return 0;
    }
}
