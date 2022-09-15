#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

// glad
#include <glad/glad.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/node.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Node::s_scope{"node"};

    Node::Node(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                              m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}
    {

        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Node()", m_file_path);
            return;
        }
        load();
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Node>(m_key, this);
        }
    }
    Node::~Node()
    {
        std::cout << " Node Clear" << std::endl;
    }

    MD5SUM Node::GetKey() { return m_key; }

    void Node::load()
    {
    }
    void Node::Use()
    {
    }

}
