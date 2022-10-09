namespace mc::asset
{
    class ArtLogicSimple;
}
#ifndef MC_ASSET_ART_LOGIC_SIMPLE_H
#define MC_ASSET_ART_LOGIC_SIMPLE_H

#include <mc/asset/act_logic.h>

namespace mc::asset
{
    class ArtLogicSimple : public ArtLogic
    {
    public: // custom uniform
            // void SetOutline(int outline);
            // void SetAmbient(float v1);
    private:
        static const std::string s_class_name;

    private:
        // glm::vec3 m_ambient;
        // glm::vec3 m_diffuse;
        // glm::vec3 m_specular;
        // float m_shininess;
        // std::string m_m_name; // 材质名字
        // int m_outline{0};

        std::shared_ptr<ShaderProgram> m_sp;

    private:
        static std::shared_ptr<ArtLogic> createFunc(const std::string &bin_data);

    public:
        ~ArtLogicSimple() override;

    public:
        static void Register(ArtLogicFactory &af);

    public:
        // virtual
        std::shared_ptr<ArtLogic> Clone() override;
        void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) override;
        void SetShaderProgram(std::shared_ptr<ShaderProgram> sp) override;
        void AddTexture(std::shared_ptr<Texture> texture) override;
        const std::string &ShowMe() override;
    };
}
#endif