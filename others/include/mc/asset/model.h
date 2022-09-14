namespace mc::asset
{
    class Model;
}
#ifndef MC_ASSET_MODEL_H
#define MC_ASSET_MODEL_H

#include <string>
#include <vector>
#include <memory>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

#include <mc/comm/pbmodel.pb.h>

namespace mc::asset
{
    class Model
    {
    public:
        Model(AssetManager &am, const std::string &file_path);
        ~Model();

    public:
        MD5SUM GetKey();
        void Use();
        int GetEBOCount();
        unsigned int GetEBOType();

    private:
        void load(); // load to gl

    private:
        const std::string m_file_path;
        MD5SUM m_key;
        std::shared_ptr<BinBuffer> m_bin_buffer;

        mc::comm::PBModel m_pb_data;
        unsigned int m_vao;
        std::vector<unsigned int> m_vbo_list;
        unsigned int m_ebo;
        int m_ebo_count;
    };
}
#endif
