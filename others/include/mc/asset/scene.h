namespace mc::asset
{
    class Scene;
}
#ifndef MC_ASSET_SCENE_H
#define MC_ASSET_SCENE_H

#include <string>
#include <vector>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbnode.pb.h>

namespace mc::asset
{
    class Scene
    {
    public:
        Scene(AssetManager &am, const std::string &file_path); // 通过文件加载的属于 Asset
        ~Scene();

    public:
        void Use();
        MD5SUM GetKey();

    private:
        void load(); // load to gl

    private:
        const std::string m_file_path;
        mc::comm::PBScene m_pb_data;
        MD5SUM m_key;
    };
}
#endif
