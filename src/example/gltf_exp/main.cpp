#include <iostream>
#include <string>
#include <fstream>
// mc glm
#include <mc/glmex/show.h>

// mc low headers
#include <mc/engine.h>
#include <game/material/simple.h>

// game headers

// comm headers
#include <mc/comm/gltf.pb.h>
#include <mc/gltf/buffer.h>

// asset headers
#include <mc/asset/md5sum.h>
#include <mc/asset/asset_manager.h>

// tools headers
#include <mc/tools/md5.h>

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
        mc::asset::AssetManager am;
        {
            // test mc::asset::Image
            auto p_image{new mc::asset::Image{am, "../others/resource/texture/mc.png"}};
            auto p_key{p_image->GetKey()};
            mc::asset::Image *rp{};
            {
                auto spimage{am.Get<mc::asset::Image>(p_key)};
                rp = spimage.get();
            }
            std::cout << "raw p_image key is " << p_key << p_image << " reg and get " << rp << std::endl;
            am.Del<mc::asset::Image>(p_key);
        }
        {
            // test mc::asset::ShaderCode
            auto p_shader_code{new mc::asset::ShaderCode{am, "../others/resource/shader/v1.vs"}};
            auto p_key{p_shader_code->GetKey()};
            mc::asset::ShaderCode *rp{};
            {
                auto sp{am.Get<mc::asset::ShaderCode>(p_key)};
                rp = sp.get();
            }
            std::cout << "raw shadercode key is " << p_key << p_shader_code << " reg and get " << rp << std::endl;
            am.Del<mc::asset::ShaderCode>(p_key);
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
