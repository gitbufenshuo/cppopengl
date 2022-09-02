#include <iostream>
#include <vector>
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mc/camera.h>
#include <mc/model.h>
#include <mc/shader.h>
#include <mc/texture.h>
#include <mc/transform.h>
#include <mc/material_phong.h>

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
        mc::low::Shader shader{"../others/resource/shader/phong.vert.vs", "../others/resource/shader/phong.frag.fs"};
        shader.Load();
        // objects
        mc::low::Transform gb_0;
        gb_0.Translate(0.0f, 0.0f, -2.0f);
        mc::low::Transform gb_1;
        gb_1.SetLocalTranslate(0.0f, 0.5f, 1.0f);
        gb_1.SetLocalScale(0.1f, 0.1f, 0.1f);
        // texture
        mc::low::Texture image{"../others/resource/texture/mc.jpeg"};
        image.Load();
        // material
        mc::low::MaterialPhong _mate_emerald{"../others/resource/material/emerald.material"};
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glm::vec3 light_color{1.0f};
        double now_time{glfwGetTime()};
        double last_time{now_time};
        const double init_time{now_time};

        while (!glfwWindowShouldClose(window))
        {
            now_time = glfwGetTime();
            std::cout << "frame interval: " << now_time - last_time << std::endl;
            last_time = now_time;
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.Use();  // shader bind
            model_0.Use(); // vao bind
            image.Use();
            shader.Uniform("ma_View", main_camera.GetViewMat());
            shader.Uniform("ma_Proj", main_camera.GetProjMat());
            {
                // logic update
                glm::sin(static_cast<float>(now_time - init_time));
                gb_1.SetLocalTranslate(glm::sin(static_cast<float>(now_time - init_time)),
                                       glm::cos(static_cast<float>(now_time - init_time)) * 10.0f,
                                       1.0f);

                shader.Uniform("lightPos", gb_1.GetWorldPos());
                shader.Uniform("lightColor", light_color);
                // gb_0.SetLocalEuler(0.0f, static_cast<float>(now_time - init_time) * 10.0f, 0.0f);
                // std::cout << "-->" << std::endl;
                // gb_0.ShowVersion();
                // gb_1.ShowVersion();
                // gb_0.Translate(0.005f, 0.0f, 0.0f);
                // gb_0.SetLocalEuler(0.0f, 0.0f, static_cast<float>(now_time - init_time) * 10.0f);
            }
            {
                // render update
                // material
                //                 vec3 ambient;
                // vec3 diffuse;
                // vec3 specular;
                // float shininess;

                // shader.Uniform("material.ambient", _mate_emerald.GetAmbient());
                // shader.Uniform("material.diffuse", _mate_emerald.GetDiffuse());
                // shader.Uniform("material.specular", _mate_emerald.GetSpecular());
                // shader.Uniform("material.shininess", _mate_emerald.GetShininess());
                // gb_0
                shader.Uniform("ma_Model", gb_0.GetWorldMat());
                glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);
                // gb_1
                shader.Uniform("ma_Model", gb_1.GetWorldMat());
                glDrawElements(GL_TRIANGLES, model_0.GetEBOCount(), GL_UNSIGNED_INT, 0);
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
    }
}
