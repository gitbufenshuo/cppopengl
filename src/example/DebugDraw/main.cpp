#include <iostream>
#include <vector>
#include <string>

#include <mc/engine.h>
#include <mc/gameobject.h>

#include <mc/model.h>
#include <mc/texture.h>
#include <mc/shader.h>

#include <mc/mesh_render.h>
#include <mc/material.h>
#include <mc/material_phong.h>
#include <mc/logic_support.h>

// game headers
#include <game/material/phong_spot.h>
#include <game/material/blinn_phong_point.h>
#include <game/material/function_chart.h>
#include <game/logic/function_draw.h>
#include <game/logic/camera_logic.h>
#include <game/example/example_list.h>

// comm headers

using mlGB = mc::low::GameObject;
using mlModel = mc::low::Model;
using mlTexture = mc::low::Texture;
using mlShader = mc::low::Shader;
using mlRender = mc::low::MeshRender;
using mlFilter = mc::low::MeshFilter;
using mlMaterial = mc::low::Material;
using mlMaterialPhong = mc::low::MaterialPhong;
namespace
{
    bool rangeshader(int key, mlShader *_shader)
    {
        std::cout << "rangeshader " << key << " " << _shader << std::endl;
        return true;
    }
    void LoadShader(mc::low::Engine &gogogo)
    {
        auto &shaderstore = gogogo.GetShaderStore();

        {
            // function chart
            auto *function_chart{new mlShader{"../others/resource/shader/function_chart.vert.vs", "../others/resource/shader/function_chart.frag.fs"}};
            function_chart->Load();
            shaderstore.Register(function_chart);
        }
        {
            auto *shader{new mlShader{"../others/resource/shader/debugtriangle.vs", "../others/resource/shader/debugtriangle.fs"}};
            shader->Load();
            shaderstore.Register(shader);
        }
        shaderstore.Range(rangeshader);
    }
    void LoadModel(mc::low::Engine &gogogo)
    {
        auto &modelstore = gogogo.GetModelStore();

        {
            // load from program
            auto *model_0{mlModel::GenerateHugeQuad(101)};
            model_0->Upload();
            modelstore.Register(model_0);
        }
    }
    void LoadTexture(mc::low::Engine &gogogo)
    {
        auto *image{new mlTexture{"../others/resource/texture/mc.jpeg"}};
        image->Load();
        auto &textruestore{gogogo.GetTextureStore()};
        textruestore.Register(image);
    }
    void LoadMaterial(mc::low::Engine &gogogo)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        /*
            材质的概念：
            1. 包含材料本身的一些颜色性质，例如 diffuse，光滑度
            2. 包含这个材质用什么 shader 去 draw
            根据这个概念，那么 phong 光照模型下，使用 point light 和 spot light 属于两种材质
            当然可以合并这两个shader，本例只是用来展示自定义 shader 的写法，按道理来说，point light 和 spot light 两种 shader
            应该合并成一种 shader 里面。(learnopengl有示例)
        */

        {
            // 加载 function chart 材质
            auto *one{new game::MaterialFunctionChart};
            one->SetShader(gogogo.GetShaderStore().Get(1));
            materialstore.Register(one);
            one->ShowMe();
        }
    }
    mlRender *GetOneRender(mc::low::Engine &gogogo, int gid)
    {
        auto &materialstore{gogogo.GetMaterialStore()};
        int mat_count = materialstore.GetCount();
        assert(mat_count);
        auto spMat{materialstore.Get(mat_count)}; //   mat_count/2 + 1 是spot phong

        auto *render{new mlRender{}};
        render->SetMaterial(spMat);
        return render;
    }
    std::vector<mlGB *> GenSome(mc::low::Engine &gogogo, mlFilter *filter)
    {
        std::vector<mlGB *> res;
        int row = 1;
        int col = 1;
        res.resize(row * col);

        for (int row_idx = 0; row_idx < row; ++row_idx)
        {
            for (int col_idx = 0; col_idx < col; ++col_idx)
            {
                auto *one = new mlGB{&gogogo};
                one->SetMeshFilter(filter);

                one->SetMeshRender(GetOneRender(gogogo, col_idx + row_idx * col));

                one->GetTransform()->SetLocalEuler(0.0f, 0.0f, 0.0f);
                one->GetTransform()->SetLocalTranslate(0.0f, 0.0f, -20.0f);
                one->AddLogicSupport(new game::FunctionDraw{one});
                one->AddLogicSupport(new game::CamereLogic{one, one->GetTransform()});
                res[row_idx * col + col_idx] = one;
            }
        }
        return res;
    }

    mlFilter *GetOneFilter(mc::low::Engine &gogogo)
    {
        auto &modelstore{gogogo.GetModelStore()};
        auto *filter_0{new mlFilter{}};
        filter_0->AddModel(modelstore.Get(1));
        return filter_0;
    }
    void ClientsetUp(GLFWwindow *window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    struct GLRenderTriangles
    {
        void create()
        {
#pragma region 创建着色器程序
            const char *V =
                "#version 330\n"
                "uniform mat4 projectionMatrix;\n"
                "layout(location = 0) in vec2 v_position;\n"
                "layout(location = 1) in vec4 v_color;\n"
                "out vec4 f_color;\n"
                "void main(void)\n"
                "{\n"
                "	f_color = v_color;\n"
                "	gl_Position = projectionMatrix*vec4(v_position, 0.0f, 1.0f);\n"

                "}\n";

            const char *F =
                "#version 330\n"
                "in vec4 f_color;\n"
                "out vec4 color;\n"
                "void main(void)\n"
                "{\n"
                "	color = f_color;\n"
                "}\n";

            unsigned vP = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vP, 1, &V, NULL);
            unsigned fP = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fP, 1, &F, NULL);

            char infolog[512];
            int success;
            glCompileShader(vP);
            glGetShaderiv(vP, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                std::cout << infolog << std::endl;
            }
            else
            {
                std::cout << "顶点着色器编译成功" << std::endl;
            }
            glCompileShader(fP);
            glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                std::cout << infolog << std::endl;
            }
            else
            {
                std::cout << "片段着色器编译成功" << std::endl;
            }

            shader = glCreateProgram();
            glAttachShader(shader, vP);
            glAttachShader(shader, fP);

            glLinkProgram(shader);
            glGetShaderiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                std::cout << infolog << std::endl;
            }
            else
            {
                std::cout << "着色器链接成功" << std::endl;
            }
            glDeleteShader(vP);
            glDeleteShader(fP);

#pragma endregion

            projection = glGetUniformLocation(shader, "projectionMatrix");
            glGenVertexArrays(1, &vaoId);
            glBindVertexArray(vaoId);
            glEnableVertexAttribArray(0); //位置属性
            glEnableVertexAttribArray(1); //颜色属性

            glGenBuffers(2, bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            m_count = 0;
        }
        void Vertex(const glm::vec2 &v, const glm::vec4 &c)
        { //在缓冲区中送入一个顶点
            if (m_count == maxCount)
            { //缓冲区的数据满了
                fflush();
            }
            vertices[m_count] = v;
            color[m_count] = c;

            m_count++;
        }
        void fflush()
        { //实际的绘制操作
            if (m_count == 0)
                return;

            glUseProgram(shader);
            float p[16] = {0.0};
            // g_camera.BuildProjectionMatrix(p, 0.0);
            glUniformMatrix4fv(projection, 1, GL_FALSE, p);
            glBindVertexArray(vaoId);

            glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), color);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawArrays(GL_TRIANGLES, 0, m_count);
            glDisable(GL_BLEND);

            glBindVertexArray(0);
            glUseProgram(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            m_count = 0;
        }
        unsigned int m_count; //点的数目
        unsigned int vaoId;   //
        unsigned int bufferId[2];
        unsigned int shader; //着色器程序
        static const int maxCount = 1024 * 32;
        glm::vec2 vertices[maxCount]; //位置
        glm::vec4 color[maxCount];    //颜色}drawtriangles;
        int projection;
    };
}

namespace game::example_list::DebugDraw
{
    int Main()
    {
        //
        mc::low::Engine gogogo{800, 800, "Hello MC"};
        gogogo.Setup(ClientsetUp);
        {
            LoadShader(gogogo);
            LoadModel(gogogo);
            LoadTexture(gogogo);
            LoadMaterial(gogogo);
            std::cout << "resource load good" << std::endl;
            auto list = GenSome(gogogo, GetOneFilter(gogogo));
            std::cout << "Gen GameObject good" << std::endl;
            for (auto one : list)
            {
                // 这个里面所有的 gameobject 都是一个 filter 和 render
                gogogo.AddGameobject(one);
            }
        }
        std::cout << "gogogo.Run()" << std::endl;
        gogogo.Run();
        return 0;
    }

}
