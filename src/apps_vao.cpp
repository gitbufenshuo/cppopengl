#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace apps::vao
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
            0.5f, -0.5f, 0.0f,  // right
            0.0f, 0.5f, 0.0f    // top
        };
        float colors[] = {
            0.0f, 0.5f, 1.0f, // left
            0.1f, 0.2f, 0.3f, // right
            0.4f, 0.5f, 0.6f  // top
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
    PROGRAM_t prepare_shader()
    {
        static const char *vertexShaderSource = "#version 330 core\n"
                                                "layout (location = 0) in vec3 aPos;\n"
                                                "layout (location = 1) in vec3 aColor;\n"
                                                "out vec3 oColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   oColor = aColor;\n"
                                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                                "}\0";
        static const char *fragmentShaderSource = "#version 330 core\n"
                                                  "out vec4 FragColor;\n"
                                                  "in vec3 oColor;\n"
                                                  "void main()\n"
                                                  "{\n"
                                                  "   FragColor = vec4(oColor, 1.0f);\n"
                                                  "}\n\0";
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }
        // link shaders
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return shaderProgram;
    }
    void draw(VAO_t vao_ins, PROGRAM_t program)
    {
        glUseProgram(program);
        glBindVertexArray(vao_ins); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    void main_loop(GLFWwindow *window)
    {
        auto vao_ins = prepare_data();
        auto program = prepare_shader();
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            draw(vao_ins, program);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}
