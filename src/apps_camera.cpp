#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mc/camera.h>
#include <mc/model.h>
#include <mc/shader.h>
#include <mc/texture.h>
#include <mc/transform.h>

namespace apps::camera
{
    void main_loop(GLFWwindow *window)
    {
        // main camera
        mc::low::Camera main_camera;
        // models
        mc::low::Model model_0{"../others/resource/model/cube.model"};
        model_0.Upload();
        // shaders
        mc::low::Shader shader{"../others/resource/shader/mvp.vs", "../others/resource/shader/mvp.fs"};
        shader.Load();
        // objects
        mc::low::Transform gb_0;
        gb_0.Translate(0.0f, -1.0f, -5.0f);
        mc::low::Transform gb_1;
        gb_1.Translate(0.0f, 1.0f, -5.0f);
        // textures
        mc::low::Texture image{"../others/resource/texture/mc.png"};
        image.Load();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.Use();  // shader bind
            model_0.Use(); // vao bind
            image.Use();
            shader.Uniform("ma_View", main_camera.GetViewMat());
            shader.Uniform("ma_Proj", main_camera.GetProjMat());
            // gb_0
            shader.Uniform("ma_Model", gb_0.GetWorldMat());
            glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);
            // gb_1
            shader.Uniform("ma_Model", gb_1.GetWorldMat());
            glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}
