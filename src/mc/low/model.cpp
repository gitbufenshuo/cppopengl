#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/model.h>
#include <mc/csv.h>

namespace mc::low
{
    Model::Model(const char *file_name) : m_file_name{file_name}
    {
        mc::tools::CSVReader<float, int, int>::Read(m_file_name, m_v_data, m_e_data, m_s_data);
    }
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
}
