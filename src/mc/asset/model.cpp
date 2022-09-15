#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

// glad
#include <glad/glad.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/model.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace
{
    void showPBDATA(mc::comm::PBModel &m_pb_data)
    {
        std::cout << "mc::asset::Model::showPBDATA "
                  << m_pb_data.bin_buffer() << " "
                  << m_pb_data.begin() << " "
                  << m_pb_data.length() << " "
                  << m_pb_data.ebo_length() << " "
                  << m_pb_data.ebo_type() << std::endl;
        throw 1;
    }
}

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string Model::s_scope{"model"};

    Model::Model(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {

        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::Model()", m_file_path);
            return;
        }
        MD5SUM bin_buffer_key;
        mc::tools::MD5Sum(m_pb_data.bin_buffer(), bin_buffer_key.data);
        m_bin_buffer = am.Get<BinBuffer>(bin_buffer_key);
        if (!m_bin_buffer)
        {
            SPD_WARN("Can't find BinBuffer ", m_pb_data.bin_buffer());
        }
        load();
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<Model>(m_key, this);
        }
    }
    Model::~Model()
    {
        std::cout << " Model Clear" << std::endl;
    }

    MD5SUM Model::GetKey() { return m_key; }

    void Model::load()
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        // 1. 先将 EBO 搞定
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_pb_data.ebo_length(), m_bin_buffer->GetData(m_pb_data.begin()), GL_STATIC_DRAW);
        // 2. 再考虑 VBO. 在文件里 load，只用一个 vbo
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        m_vbo_list.push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, m_pb_data.length() - m_pb_data.ebo_length(), m_bin_buffer->GetData(m_pb_data.begin() + m_pb_data.ebo_length()), GL_STATIC_DRAW);
        if (m_pb_data.ebo_type() == GL_UNSIGNED_INT)
        {
            m_ebo_count = m_pb_data.ebo_length() / 4;
        }
        else if (m_pb_data.ebo_type() == GL_UNSIGNED_SHORT)
        {
            m_ebo_count = m_pb_data.ebo_length() / 2;
        }

        // 3. vertex attrib
        int total{0};
        int offset{0};
        for (int location = 0; location < m_pb_data.attrib_size(); ++location)
        {
            total += m_pb_data.attrib(location);
        }
        for (int location = 0; location < m_pb_data.attrib_size(); ++location)
        {
            glVertexAttribPointer(location, m_pb_data.attrib(location), GL_FLOAT, GL_FALSE, total * sizeof(float), (void *)(offset * sizeof(float)));
            glEnableVertexAttribArray(location);
            offset += m_pb_data.attrib(location);
        }
    }
    void Model::Use()
    {
        glBindVertexArray(m_vao);
    }
    int Model::GetEBOCount()
    {
        return m_ebo_count;
    }
    unsigned int Model::GetEBOType()
    {
        return m_pb_data.ebo_type();
    }
}
