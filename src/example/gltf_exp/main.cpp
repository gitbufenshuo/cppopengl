#include <iostream>
#include <string>
#include <fstream>
// mc glm
#include <mc/glmex/show.h>

// mc low headers
#include <mc/engine.h>

// game headers

// comm headers
#include <mc/comm/pbdirspec.pb.h>

// asset headers
#include <mc/asset/md5sum.h>
#include <mc/asset/asset_manager.h>

// tools headers
#include <mc/tools/md5.h>

// log
#include <mc/log/log.h>

namespace
{

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

    void loadSceneFromFile(mc::low::Engine &gogogo, const char *dir_spec_path)
    {
        std::ifstream t(dir_spec_path);
        mc::comm::PBDirSpec pb_data;
        if (!pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("loadSceneFromFile()", dir_spec_path);
            throw 1;
        }
        //
    }

}

namespace game::example_list::gltf_exp
{
    int Main()
    {
        mc::low::Engine gogogo{800, 800, "Hello Scene Load"};
        loadSceneFromFile(gogogo, "");
    }
}
