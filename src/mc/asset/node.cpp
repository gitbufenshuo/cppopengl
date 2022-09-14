#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

    Node::Node(AssetManager &am, const std::string &file_path) : m_file_path{file_path}
    {

        std::ifstream t(file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Node()", file_path);
            return;
        }
        load();
        mc::tools::MD5Sum(file_path, m_key.data);
        am.Reg<Node>(m_key, this);
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
