#include <iostream>
#include <string>
#include <fstream>
// glm

// mc low headers
#include <mc/engine.h>
#include <game/material/simple.h>

// game headers

// comm headers
#include <mc/comm/gltf.pb.h>
#include <mc/gltf/buffer.h>

// asset headers
#include <mc/asset/asset_manager.h>

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
    int testGLTF()
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
    int testAssetManager()
    {
        mc::asset::AssetManager am{};
        {
            // test mc::asset::Image
            auto p_image{new mc::asset::Image{"../others/resource/texture/mc.png"}};
            mc::asset::MD5SUM key{};
            am.Reg<mc::asset::Image>(key, p_image);
            mc::asset::Image *rp{};
            {
                auto spimage{am.Get<mc::asset::Image>(key)};
                rp = spimage.get();
            }
            std::cout << "raw p_image " << p_image << " reg and get " << rp << std::endl;
            am.Del<mc::asset::Image>(key);
        }
        {
            // test mc::asset::ShaderCode
            auto p_shader_code{new mc::asset::ShaderCode{"../others/resource/shader/v1.vs"}};
            mc::asset::MD5SUM key{};
            am.Reg<mc::asset::ShaderCode>(key, p_shader_code);
            mc::asset::ShaderCode *rp{};
            {
                auto sp{am.Get<mc::asset::ShaderCode>(key)};
                rp = sp.get();
            }
            std::cout << "raw shadercode " << p_shader_code << " reg and get " << rp << std::endl;
            am.Del<mc::asset::ShaderCode>(key);
        }
        std::cout << "AssetManager Test OK" << std::endl;
        return 0;
    }
}

namespace game::example_list::gltf_exp
{
    int Main()
    {
        return testAssetManager();
    }
}
