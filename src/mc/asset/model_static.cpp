#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mc/asset/model.h>

namespace mc::asset
{
    /**
     * @brief 生成一个标准的cube可以当做cubemap来用的
     *
     * @return std::shared_ptr<Model>
     */
    std::shared_ptr<Model> Model::CreateCubemap()
    {
        auto res{std::make_shared<Model>()};
        glGenVertexArrays(1, &res->m_vao);
        glBindVertexArray(res->m_vao);
        // vbo 八个点
        float vert_list[] = {
            -0.5f, -0.5f, 0.5f, // 0
            0.5f, -0.5f, 0.5f,  // 1
            0.5f, 0.5f, 0.5f,   // 2
            -0.5f, 0.5f, 0.5f,  // 3

            -0.5f, -0.5f, -0.5f, // 4
            0.5f, -0.5f, -0.5f,  // 5
            0.5f, 0.5f, -0.5f,   // 6
            -0.5f, 0.5f, -0.5f   // 7
        };
        unsigned short ebo_list[] = {
            1, 2, 5, 5, 2, 6, // x
            3, 7, 2, 2, 7, 6, // y
            0, 2, 1, 0, 3, 2, // z

            0, 4, 3, 4, 7, 3, // -x
            0, 1, 4, 1, 5, 4, // -y
            4, 6, 7, 4, 5, 6  // -z
        };
        // ebo
        glGenBuffers(1, &res->m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res->m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebo_list), &ebo_list, GL_STATIC_DRAW);
        res->m_ebo_type = GL_UNSIGNED_SHORT;
        res->m_ebo_count = std::size(ebo_list);
        // vbo
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        res->m_vbo_list.push_back(vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vert_list), &vert_list, GL_STATIC_DRAW);
        // attrib
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)(0));
        return res;
    }
}