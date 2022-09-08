#include <iostream>
#include <string>
#include <fstream>
// mc low headers
#include <mc/engine.h>
#include <game/material/simple.h>

// game headers

// comm headers
#include <mc/comm/gltf.pb.h>
#include <mc/gltf/buffer.h>

using mlShader = mc::low::Shader;

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
            auto *_shader{new mlShader{"../others/resource/shader/simple.vert.vs", "../others/resource/shader/simple.frag.fs"}};
            _shader->Load();
            shaderstore.Register(_shader);
        }
    }

    void LoadMaterial(mc::low::Engine &gogogo)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        {
            // 加载 simple 材质
            auto ma{new game::MaterialSimple{}};
            ma->SetShader(gogogo.GetShaderStore().Get(1));
            materialstore.Register(ma);
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
