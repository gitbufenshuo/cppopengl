namespace mc::asset
{
    class ArtLogic;
    class ArtLogicFactory;
}

#ifndef MC_ASSET_ART_LOGIC_H
#define MC_ASSET_ART_LOGIC_H

#include <string>
#include <vector>
#include <memory>
#include <utility>

// glm
#include <glm/glm.hpp>

// mc::low
#include <mc/engine.h>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

// proto types
#include <mc/comm/pbartlogic.pb.h>

namespace mc::asset
{
    class ArtLogic
    {
    public:
        ArtLogic() = default;
        ArtLogic(AssetManager &am, const std::string &file_path);
        virtual void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) {}
        virtual void SetShaderProgram(std::shared_ptr<ShaderProgram> sp) {}
        virtual void AddTexture(std::shared_ptr<Texture> texture) {}
        virtual void ShowMe() {}
        virtual ~ArtLogic();

    public:
        MD5SUM GetKey();
        const std::string &GetLogicName();
        const std::string &GetBinData();

    private:
        const std::string m_file_path;
        MD5SUM m_key;
        mc::comm::PBArtLogic m_pb_data;
    };

    class ArtLogicFactory
    {
    public:
        using CreateFunc = std::shared_ptr<ArtLogic> (*)(const std::string &bin_data);
        // 引擎初始化的时候，必须将自定义的 ArtLogic 手动注册到这里
        void Register(const std::string &class_name, CreateFunc);
        std::shared_ptr<ArtLogic> Create(const std::string &class_name, const std::string &bin_data);

    private:
        CreateFunc getFunc(const std::string &class_name);

    private:
        std::vector<std::pair<std::string, CreateFunc>> m_holder;
    };

    class ArtLogicPhong : public ArtLogic
    {
    private:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        float m_shininess;
        std::string m_m_name; // 材质名字

        std::shared_ptr<ShaderProgram> m_sp;
        std::shared_ptr<Texture> m_texture;

    private:
        static std::shared_ptr<ArtLogic> createFunc(const std::string &bin_data);

    public:
        ~ArtLogicPhong() override;

    public:
        static void Register(ArtLogicFactory &af);

    public:
        // virtual
        void PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb) override;
        void SetShaderProgram(std::shared_ptr<ShaderProgram> sp) override;
        void AddTexture(std::shared_ptr<Texture> texture) override;
        void ShowMe() override;
    };
}
#endif
