#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace apps::init
{
    void main_loop(GLFWwindow *window)
    {
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            // processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}
