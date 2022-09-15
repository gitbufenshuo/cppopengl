namespace mc::asset
{
    class Node;
}
#ifndef MC_ASSET_NODE_H
#define MC_ASSET_NODE_H

#include <string>
#include <vector>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbnode.pb.h>

namespace mc::asset
{
    class Node
    {
    public:
        Node(AssetManager &am, const std::string &r_name); // 通过文件加载的属于 Asset
        ~Node();

    public:
        void Use();
        MD5SUM GetKey();

    private:
        void load(); // load to gl

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        mc::comm::PBNode m_pb_data;
        MD5SUM m_key;
    };
}
#endif
