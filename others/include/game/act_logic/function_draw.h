#ifndef GAME_LOGIC_FUNCTION_DRAW_H
#define GAME_LOGIC_FUNCTION_DRAW_H

#include <mc/gameobject.h>

#include <mc/asset/act_logic.h>

namespace game
{
    class ArtLogicFunctionDraw : public mc::asset::ActLogic
    {
    private:
        static std::shared_ptr<ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        ~ArtLogicFunctionDraw() override;

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time, unsigned int layer) override;
        void AfterRenderUpdate(double delta_time, unsigned int layer) override;
    };
}

#endif