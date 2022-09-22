namespace mc::asset
{
    class ActLogic;
    class ActLogicFactory;
}

#ifndef MC_ASSET_ACT_LOGIC_H
#define MC_ASSET_ACT_LOGIC_H

#include <string>
#include <vector>
#include <memory>
#include <utility>

// glm
#include <glm/glm.hpp>

// mc::low
#include <mc/engine.h>
#include <mc/gameobject.h>
#include <mc/transform.h>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>

// proto types
#include <mc/comm/pbactlogic.pb.h>

namespace mc::asset
{
    class ActLogic
    {
    public:
        ActLogic() = default;
        ActLogic(AssetManager &am, const std::string &r_name);
        virtual ~ActLogic();

    public:
        virtual void Update(double delta_time){};
        virtual void BeforeRenderUpdate(double delta_time, unsigned int layer){};
        virtual void AfterRenderUpdate(double delta_time, unsigned int layer){};

    public:
        MD5SUM GetKey();
        const std::string &GetLogicName();
        const std::string &GetBinData();

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // act_logic

        MD5SUM m_key;
        mc::comm::PBActLogic m_pb_data;

    protected:
        mc::low::GameObject *m_gb;
    };
}
namespace mc::asset
{
    class ActLogicFactory
    {
    public:
        using CreateFunc = std::shared_ptr<ActLogic> (*)(mc::low::GameObject *gb, const std::string &bin_data);
        // 引擎初始化的时候，必须将自定义的 ActLogic 手动注册到这里
        // 或者使用脚本扫描
        void Register(const std::string &class_name, CreateFunc);
        std::shared_ptr<ActLogic> Create(mc::low::GameObject *gb, const std::string &class_name, const std::string &bin_data);

    private:
        CreateFunc getFunc(const std::string &class_name);

    private:
        std::vector<std::pair<std::string, CreateFunc>> m_holder;
    };
}

namespace mc::asset
{
    class ActLogicCamera : public mc::asset::ActLogic
    {
        mc::low::Transform *m_ctl_transform;
        float m_now_yaw{0.0f};
        float m_now_pitch{0.0f};

    private:
        static std::shared_ptr<ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        ~ActLogicCamera() override;

    public:
        static void Register(ActLogicFactory &acf);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time, unsigned int layer) override;
        void AfterRenderUpdate(double delta_time, unsigned int layer) override;
    };

}
#endif
