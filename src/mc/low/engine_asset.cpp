#include <fstream>
#include <vector>
// mc::low
#include <mc/engine.h>
#include <mc/mesh_render.h>
#include <mc/engine.h>

// asset
#include <mc/asset/md5sum.h>
// tools
#include <mc/tools/md5.h>
// comm headers
#include <mc/comm/pbdirspec.pb.h>
// log
#include <mc/log/log.h>

namespace
{

    void buildOnePBNode(mc::low::Engine *gogogo, const mc::comm::PBNode &one_node, mc::low::Transform *up, std::vector<mc::low::GameObject *> &gb_list)
    {
        auto &am{*gogogo->GetAM()};
        auto newgb{new mc::low::GameObject{gogogo}};
        gb_list.push_back(newgb);
        newgb->GetTransform()->SetLocalTranslate(one_node.transform().translate().x(),
                                                 one_node.transform().translate().y(),
                                                 one_node.transform().translate().z());
        newgb->GetTransform()->SetLocalRotation(one_node.transform().rotation().w(),
                                                one_node.transform().rotation().x(),
                                                one_node.transform().rotation().y(),
                                                one_node.transform().rotation().z());
        {
            // mesh filter
            auto mf{new mc::low::MeshFilter{}};
            mf->AddModel(am.Get<mc::asset::Model>()); // 暂时
            // mesh render
            auto mr{new mc::low::MeshRender{}};
            mr->SetGameobject(newgb);
            mr->SetMaterial(am.Get<mc::asset::Material>()); // 暂时
            newgb->SetMeshFilter(mf);
            newgb->SetMeshRender(mr);
        }
        {
            // act logic
            auto &act_factory{am.GetACF()};
            for (int index = 0; index < one_node.act_logic_list_size(); ++index)
            {
                auto metaActLogic{am.Get<mc::asset::ActLogic>(one_node.act_logic_list(index))};
                auto realActLogic{act_factory.Create(newgb, metaActLogic->GetLogicName(), metaActLogic->GetBinData())};
                newgb->AddAct(realActLogic);
            }
        }
        if (up)
        {
            newgb->GetTransform()->SetUpper(up);
        }
        // sub_list
        for (int index = 0; index < one_node.sub_list_size(); ++index)
        {
            buildOnePBNode(gogogo, one_node.sub_list(index), newgb->GetTransform(), gb_list);
        }
    }
    void createDefualtScene(mc::low::Engine *gogogo, mc::comm::PBDirSpec &pb_data)
    {
        auto &am{*gogogo->GetAM()};
        mc::asset::MD5SUM _key;
        mc::tools::MD5Sum(pb_data.scene_list(0), _key.data);
        auto firstScene{am.Get<mc::asset::Scene>(_key)};
        // 生成整个场景里的 GameObject
        std::vector<mc::low::GameObject *> gb_list;
        for (int index = 0; index < firstScene->GetPBNodeSize(); ++index)
        {
            buildOnePBNode(gogogo, firstScene->GetPBNode(index), nullptr, gb_list);
        }
        for (auto one_gb : gb_list)
        {
            gogogo->AddGameobject(one_gb);
        }
    }
}

namespace mc::low
{
    void Engine::LoadAssetAndCreate(const char *file_path)
    {
        auto &am{*GetAM()};
        std::ifstream t(file_path);
        mc::comm::PBDirSpec pb_data;
        if (!pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("loadSceneFromFile()", file_path);
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
        // load ActLogic
        for (int index = 0; index < pb_data.act_logic_list_size(); ++index)
        {
            new mc::asset::ActLogic{am, pb_data.act_logic_list(index)};
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
        createDefualtScene(this, pb_data);
    }
}