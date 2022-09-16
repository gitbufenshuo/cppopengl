#include <iostream>
#include <vector>
#include <string>

#include <mc/engine.h>
#include <mc/gameobject.h>

#include <mc/mesh_render.h>

// game headers
#include <game/act_logic/box_draw.h>
#include <game/example/example_list.h>

// comm headers

using mlGB = mc::low::GameObject;
namespace
{
    void registActLogic(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        // 这一步必须手动
        // 或者借助于命令行自动扫描生成
        game::BoxDraw::Register(am.GetACF());
    }

    std::vector<mlGB *> GenSome(mc::low::Engine &gogogo)
    {
        auto &am{*gogogo.GetAM()};
        auto &act_factory{am.GetACF()};

        std::vector<mlGB *> res;
        int row = 1;
        int col = 1;
        res.resize(row * col);
        for (int row_idx = 0; row_idx < row; ++row_idx)
        {
            for (int col_idx = 0; col_idx < col; ++col_idx)
            {
                auto *one = new mlGB{&gogogo};
                one->GetTransform()->SetLocalEuler(0.0f, 0.0f, 0.0f);
                one->GetTransform()->SetLocalTranslate(0.0f, 0.0f, -20.0f);
                one->AddAct(act_factory.Create(one, "game::act_logic::BoxDraw", ""));
                res[row_idx * col + col_idx] = one;
            }
        }
        return res;
    }
    void ClientsetUp(GLFWwindow *window)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        game::BoxDraw::g_camera.window = window;
    }
}
namespace game::example_list::DebugDraw
{
    int Main()
    {
        mc::low::Engine gogogo{1600, 900, "Hello MC"};
        gogogo.Setup(ClientsetUp);
        registActLogic(gogogo);
        {
            auto list = GenSome(gogogo);
            for (auto one : list)
            {
                gogogo.AddGameobject(one);
            }
        }
        std::cout << "gogogo.Run()" << std::endl;
        gogogo.Run();
        return 0;
    }
}
