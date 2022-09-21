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
        Model(AssetManager &am, const std::string &r_name);
        Model() = default;
        ~Model();

    public:
        MD5SUM GetKey();
        void Use();
        int GetEBOCount();
        unsigned int GetEBOType();

    public:
        static std::shared_ptr<Model> CreateCubemap();

    private:
        void load(); // load to gl

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // bin_buffer

        MD5SUM m_key;
        std::shared_ptr<BinBuffer> m_bin_buffer;

        mc::comm::PBModel m_pb_data;
        unsigned int m_vao;
        std::vector<unsigned int> m_vbo_list;
        unsigned int m_ebo;
        int m_ebo_count;
        int m_ebo_type;
    };
}
#endif
