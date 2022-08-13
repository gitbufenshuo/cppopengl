#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mc/shader.h>

namespace apps::xyzw
{
    using VAO_t = unsigned int;
    using PROGRAM_t = unsigned int;
    // 创建两个 vbo
    // vbo1 用来存放坐标
    // vbo2 用来存放颜色
    // 用一个 vao 控制两个 vbo
    VAO_t prepare_data()
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.0f, 0.5f, 0.0f,   // top
            0.5f, -0.5f, 0.0f,  // right
        };
        float colors[] = {
            1.0f, 1.0f, 1.0f, // left
            0.5f, 0.5f, 0.5f, // top
            0.0f, 0.0f, 0.0f, // right
        };

        VAO_t VBO1, VBO2, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO1);
        glGenBuffers(1, &VBO2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return VAO;
    }
    void draw(VAO_t vao_ins, const mc::low::Shader &shader)
    {
        shader.Use();
        glBindVertexArray(vao_ins); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    void main_loop(GLFWwindow *window)
    {
        auto vao_ins = prepare_data();
        mc::low::Shader shader{"../others/resource/shader/v1.vs", "../others/resource/shader/v1.fs"};
        shader.Load();
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            draw(vao_ins, shader);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}
