#include <cassert> // for assert()
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/model.h>
#include <mc/csv.h>

namespace mc::low
{
    // constructors
    Model::Model(const char *file_name) : m_file_name{file_name}
    {
        mc::tools::CSVReader<float, int, int>::Read(m_file_name, m_v_data, m_e_data, m_s_data);
    }
    Model::Model()
    {
    }
    // normal method
    void Model::Upload()
    {
        if (m_uploaded)
        {
            return;
        }
        m_uploaded = true;
        //
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);
        //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_v_data.size() * sizeof(float), m_v_data.data(), GL_STATIC_DRAW);
        //
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
        // ebo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_e_data.size(), m_e_data.data(), GL_STATIC_DRAW);
    }
    void Model::Use()
    {
        glBindVertexArray(m_vao);
    }
    int Model::GetEBOCount() const
    {
        return static_cast<int>(m_e_data.size());
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
        res->m_e_data.reserve((edge - 1) * (edge - 1) * 3);
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
            // res->m_e_data.push_back(index / 2);
            // res->m_e_data.push_back(index / 2 + edge + 1);
            // res->m_e_data.push_back(index / 2 + 1);
        }
        res->m_s_data.push_back(2);
        // std::cout << "GenerateHugeQuad:: ebo size " << res->m_e_data.size() << " " << res->m_e_data[res->m_e_data.size() - 1] << std::endl;
        // std::cout << "GenerateHugeQuad:: vdata size " << res->m_v_data.size() << " " << res->m_v_data[0] << std::endl;
        for (int index = 0; index < 3; ++index)
        {
            std::cout << "GenerateHugeQuad index: " << index << " -> " << res->m_v_data[res->m_e_data[index] * 2] << ", " << res->m_v_data[res->m_e_data[index] * 2 + 1] << std::endl;
        }
        return res;
    }
}
