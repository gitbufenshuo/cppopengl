#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// glad
#include <glad/glad.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/scene.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{

    Scene::Scene(AssetManager &am, const std::string &file_path) : m_file_path{file_path}
    {

        std::ifstream t(file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Scene()", file_path);
            return;
        }
        load();
        mc::tools::MD5Sum(file_path, m_key.data);
        am.Reg<Scene>(m_key, this);
    }
    Scene::~Scene()
    {
        std::cout << " Scene Clear" << std::endl;
    }

    MD5SUM Scene::GetKey() { return m_key; }

    void Scene::load()
    {
    }
    void Scene::Use()
    {
    }

}
