#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace apps::math
{
    namespace
    {
        void showVec(const glm::vec3 &input)
        {
            std::cout << "        " << input.x << " "
                      << input.y << " "
                      << input.z << " "
                      << std::endl;
        }
        void showMat(const glm::mat4 &input)
        {
            std::cout << "---show mat---" << std::endl;
            for (int row = 0; row < 4; ++row)
            {
                for (int col = 0; col < 4; ++col)
                {
                    std::cout << input[col][row] << " ";
                }
                std::cout << std::endl;
            }
        }
        void testPerspective()
        {
            glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 100.0f);
            showMat(proj);
            for (float z = -1.1f; z >= -99.0f; z -= 0.5f)
            {

                glm::vec4 my_vec(0.0f, 0.0f, z, 1.0f);
                my_vec = proj * my_vec;
                std::cout << z << " xyzw:[" << my_vec.x << " "
                          << my_vec.y << " "
                          << my_vec.z << " "
                          << my_vec.w << std::endl;
            }
        }
        void testVec3Mul()
        {
            glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
            glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
            glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);

            showVec(result);
        }
        void testTranslate()
        {
            glm::mat4 trans = glm::mat4(1.0f); // 单位阵
            trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));
            showMat(trans);
        }
        void testQuaternion()
        {
            // [cos(0.5 jiaodu), sin(0.5 jiaodu)(x y z) ]
            auto cos_45_2 = glm::cos(glm::radians(45.0f / 2.0f));
            auto sin_45_2 = glm::sin(glm::radians(45.0f / 2.0f));
            glm::quat quat_x = glm::quat(cos_45_2, sin_45_2, 0, 0); // 绕 x 转 45
            glm::quat quat_y = glm::quat(cos_45_2, 0, sin_45_2, 0); // 绕 y 转 45
            glm::quat quat_z = glm::quat(cos_45_2, 0, 0, sin_45_2); // 绕 z 转 45
            auto quat_yx = glm::cross(quat_y, quat_x);              // y45 x45
            auto quat_zyx = glm::cross(quat_z, quat_yx);            // z45 y45 x45
            auto mat = glm::toMat4(quat_zyx);
            showMat(mat);
            //
            glm::vec4 testvec{1.0f, 1.0f, 1.0f, 1.0f};
            auto res = mat * testvec;
            showVec(res);
            {
                auto v3 = glm::eulerAngles(quat_zyx);
                // showVec(v3);
                auto v3de = glm::degrees(v3);
                showVec(v3de);
                glm::mat4 trans = glm::mat4(1.0f);                          // 单位阵
                trans = glm::rotate(trans, v3.z, glm::vec3(0.0, 0.0, 1.0)); // z
                trans = glm::rotate(trans, v3.y, glm::vec3(0.0, 1.0, 0.0)); // y
                trans = glm::rotate(trans, v3.x, glm::vec3(1.0, 0.0, 0.0)); // x
                showMat(trans);
                glm::vec4 testvec{1.0f, 1.0f, 1.0f, 1.0f};
                auto res = trans * testvec;
                showVec(res);
            }
        }
        void testMat()
        {
            glm::mat4 mat{1.0f};
            showMat(mat);
        }
    }
    // -Wno-unused-function
    void main_loop(GLFWwindow *window)
    {
        // testMat();
        // testQuaternion();
        // testTranslate();
        // testVec3Mul();
        testPerspective();
    }
}