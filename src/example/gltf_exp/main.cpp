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

    void registArtLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        mc::asset::ArtLogicPhong::Register(am.GetAF());
    }
    void loadSceneFromFile(mc::low::Engine &gogogo, const char *dir_spec_path)
    {
        auto &am{*gogogo.GetAM()};
        std::ifstream t(dir_spec_path);
        mc::comm::PBDirSpec pb_data;
        if (!pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("loadSceneFromFile()", dir_spec_path);
            throw 1;
        }
        am.SetBaseDir(pb_data.base_dir());
        // load Image
        for (int index = 0; index < pb_data.image_list_size(); ++index)
        {
            new mc::asset::Image{am, pb_data.image_list(index)};
        }
        // load BinBuffer
        for (int index = 0; index < pb_data.bin_buffer_list_size(); ++index)
        {
            new mc::asset::BinBuffer{am, pb_data.bin_buffer_list(index)};
        }
        // load ShaderCode
        for (int index = 0; index < pb_data.shader_code_list_size(); ++index)
        {
            new mc::asset::ShaderCode{am, pb_data.shader_code_list(index)};
        }
        // load ArtLogic
        for (int index = 0; index < pb_data.art_logic_list_size(); ++index)
        {
            new mc::asset::ArtLogic{am, pb_data.art_logic_list(index)};
        }
        // load Texture
        for (int index = 0; index < pb_data.texture_list_size(); ++index)
        {
            new mc::asset::Texture{am, pb_data.texture_list(index)};
        }
        // load Model
        for (int index = 0; index < pb_data.model_list_size(); ++index)
        {
            new mc::asset::Model{am, pb_data.model_list(index)};
        }
        // load ShaderProgram
        for (int index = 0; index < pb_data.shader_program_list_size(); ++index)
        {
            new mc::asset::ShaderProgram{am, pb_data.shader_program_list(index)};
        }
        // load Material
        for (int index = 0; index < pb_data.material_list_size(); ++index)
        {
            new mc::asset::Material{am, pb_data.material_list(index)};
        }
        // load scene
        for (int index = 0; index < pb_data.scene_list_size(); ++index)
        {
            new mc::asset::Scene{am, pb_data.scene_list(index)};
        }
    }

}

namespace game::example_list::gltf_exp
{
    int Main()
    {
        mc::low::Engine gogogo{800, 800, "Hello Scene Load"};
        registArtLogic(gogogo);
        loadSceneFromFile(gogogo, "gogogo.pb.data");
        return 0;
    }
}
