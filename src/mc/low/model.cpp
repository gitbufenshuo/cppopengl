#include <cstdlib> // for rand
#include <cassert> // for assert()
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/model.h>
#include <mc/csv.h>

namespace mc::low
{
    // constructors
    Model::Model(const char *file_name, bool append) : m_file_name{file_name}
    {
        mc::tools::CSVReader<float, int, int>::Read(m_file_name, m_v_data, m_e_data, m_s_data);
        m_ebo_size = m_e_data.size();
        //
        if (append)
        {
            int stride{0};
            for (auto one : m_s_data)
            {
                stride += one;
            }
            int raw_v_size = static_cast<int>(m_v_data.size());
            int raw_e_size = static_cast<int>(m_e_data.size());
            m_v_data.resize(m_v_data.size() * 4);
            float offset{1.0f};
            float scale{0.2f};
            // v - z -append
            for (int index = raw_v_size; index < 2 * raw_v_size; index += stride)
            {
                m_v_data[index] = m_v_data[index - raw_v_size] * scale;
                m_v_data[index + 1] = m_v_data[index - raw_v_size + 1] * scale;
                m_v_data[index + 2] = m_v_data[index - raw_v_size + 2] + offset;
            }
            // v - x -append
            for (int index = 2 * raw_v_size; index < 3 * raw_v_size; index += stride)
            {
                m_v_data[index] = m_v_data[index - 2 * raw_v_size] + offset;
                m_v_data[index + 1] = m_v_data[index - 2 * raw_v_size + 1] * scale;
                m_v_data[index + 2] = m_v_data[index - 2 * raw_v_size + 2] * scale;
            }
            // v - y -append
            for (int index = 3 * raw_v_size; index < 4 * raw_v_size; index += stride)
            {
                m_v_data[index] = m_v_data[index - 3 * raw_v_size] * scale;
                m_v_data[index + 1] = m_v_data[index - 3 * raw_v_size + 1] + offset;
                m_v_data[index + 2] = m_v_data[index - 3 * raw_v_size + 2] * scale;
            }
            m_e_data.resize(m_e_data.size() * 4);
            for (int index = raw_e_size; index < 4 * raw_e_size; ++index)
            {
                m_e_data[index] = m_e_data[index - raw_e_size] + 24;
            }
            m_ebo_size = m_e_data.size();
        }
    }

    Model::Model(bool init_vao)
    {
        if (init_vao)
        {
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);
        }
    }

    void Model::SetGLID(unsigned int vbo, unsigned int ebo, unsigned int ebo_type, int ebo_size)
    {
        m_vbo = vbo;
        m_ebo = ebo;
        m_ebo_type = ebo_type;
        m_ebo_size = ebo_size;
    }

    void Model::SetAttr(int loc, int size, int stride, void *pointer)
    {
        std::cout << "Model::SetAttr " << loc << " " << size << " " << stride << " " << pointer << std::endl;
        glBindVertexArray(m_vao);
        glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, stride, pointer);
        glEnableVertexAttribArray(loc);
    }

    // normal method
    void Model::Upload()
    {
        if (m_uploaded)
        {
            return;
        }
        m_uploaded = true;
        m_ebo_size = m_e_data.size();
        m_ebo_type = GL_UNSIGNED_INT;
        //
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glGenBuffers(1, &m_vbo);
        if (m_v_data1.size() > 0)
        {
            glGenBuffers(1, &m_vbo1);
        }
        glGenBuffers(1, &m_ebo);
        //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_v_data.size() * sizeof(float), m_v_data.data(), GL_STATIC_DRAW);
        if (m_vbo1 > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
            glBufferData(GL_ARRAY_BUFFER, m_v_data1.size() * sizeof(float), m_v_data1.data(), GL_STATIC_DRAW);
        }
        //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        int _loc = 0;
        int _total = 0;
        int _off = 0;
        for (auto one : m_s_data)
        {
            _total += one;
        }

        for (auto one : m_s_data)
        {
            glVertexAttribPointer(_loc, one, GL_FLOAT, GL_FALSE, _total * sizeof(float), (void *)(_off * sizeof(float)));
            glEnableVertexAttribArray(_loc);
            ++_loc;
            _off += one;
        }
        if (m_vbo1 > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
            int _total = 0;
            int _off = 0;
            for (auto one : m_s_data1)
            {
                _total += one;
            }

            for (auto one : m_s_data1)
            {
                glVertexAttribPointer(_loc, one, GL_FLOAT, GL_FALSE, _total * sizeof(float), (void *)(_off * sizeof(float)));
                glEnableVertexAttribArray(_loc);
                ++_loc;
                _off += one;
            }
        }
        // ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_e_data.size(), m_e_data.data(), GL_STATIC_DRAW);
    }
    void Model::Use()
    {
        // std::cout << "vao: " << m_vao << " vbo: " << m_vbo << " ebo: " << m_ebo << std::endl;
        glBindVertexArray(m_vao);
    }
    int Model::GetEBOCount() const
    {
        return m_ebo_size;
    }
    unsigned int Model::GetEBOType() const
    {
        return m_ebo_type;
    }

    // 生成一个巨大的多顶点quad, 正方形，边长的点数是edge
    // 确保 edge 是奇数且 >= 3
    Model *Model::GenerateHugeQuad(int edge)
    {
        assert(!(edge < 3 || edge % 2 == 0) && "确保 edge 是奇数且 >= 3");
        // 首先 总的顶点数是 edge * edge
        auto *res{new Model};
        res->m_v_data.reserve(edge * edge);
        // x z
        float min = -static_cast<float>(edge / 2);
        for (int x = min; x <= -min; x += 1.0f)
        {
            for (int z = min; z <= -min; z += 1.0f)
            {
                res->m_v_data.push_back(x);
                res->m_v_data.push_back(z);
            }
        }
        int totallen = static_cast<int>(res->m_v_data.size());
        // ebo
        res->m_e_data.reserve((edge - 1) * (edge - 1) * 6);
        for (int index = 0; index < totallen; ++index)
        {
            if (index % 2 == 1)
            {
                continue;
            }
            if (((index / 2) + 1) % edge == 0)
            {
                continue;
            }
            if ((index / 2) >= (edge * (edge - 1)))
            {
                break;
            }
            // append ebo
            res->m_e_data.push_back(index / 2);
            res->m_e_data.push_back(index / 2 + edge);
            res->m_e_data.push_back(index / 2 + edge + 1);
            //
            res->m_e_data.push_back(index / 2);
            res->m_e_data.push_back(index / 2 + edge + 1);
            res->m_e_data.push_back(index / 2 + 1);
        }
        res->m_s_data.push_back(2);
        res->m_s_data1.push_back(3);
        // 对这些点生成颜色数据
        res->m_v_data1.resize(res->m_v_data.size() * 3 / 2); // 颜色数据
        for (auto &one : res->m_v_data1)
        {
            one = static_cast<float>(rand() % 100) / 100.0f;
        }
        return res;
    }
    void Model::TestChangeData1(float factor)
    {
        if (m_vbo1)
        {
            Use();
            glDeleteBuffers(1, &m_vbo1);
            glGenBuffers(1, &m_vbo1);
            for (auto &one : m_v_data1)
            {
                one = (factor += 0.01);
                if (factor > 1.0)
                {
                    factor = 0.0;
                }
            }
            //
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
            //
            glBufferData(GL_ARRAY_BUFFER, m_v_data1.size() * sizeof(float), m_v_data1.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0 * sizeof(float)));
        }
    }
}
