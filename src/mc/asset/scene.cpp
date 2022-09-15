#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

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
    using stdpath = std::filesystem::path;
    const std::string Scene::s_scope{"scene"};

    Scene::Scene(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {

        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Scene()", m_file_path);
            return;
        }
        load();
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Scene>(m_key, this);
        }
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
