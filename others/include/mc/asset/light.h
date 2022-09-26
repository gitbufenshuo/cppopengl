namespace mc::asset
{
    class Light;
}
#ifndef MC_ASSET_LIGHT_H
#define MC_ASSET_LIGHT_H

#include <string>
#include <string_view>

#include <glm/glm.hpp>

#include <mc/asset/asset_manager.h>
#include <mc/asset/md5sum.h>
#include <mc/comm/pbnode.pb.h>

namespace mc::asset
{
    class Light
    {
    public:
        enum class Kind
        {
            Direction,
            Point,
            Spot
        };

    public:
        Light() = default;
        Light(AssetManager &am, const std::string &r_name);
        ~Light();
        Light(const Light &other);

    public:
        MD5SUM GetKey();
        void SetPos(glm::vec3 pos);
        void SetForward(glm::vec3 forward);
        void SetColor(glm::vec3 color);
        void SetAttenuation(glm::vec3 attenuation);
        void SetKind(Kind kind);

        const glm::vec3 &GetPos() const;
        const glm::vec3 &GetForward() const;
        const glm::vec3 &GetColor() const;
        const glm::vec3 &GetAttenuation() const;
        int GetKind() const;

        std::shared_ptr<Light> Clone() const;

    private:
        void load();

    private:
        const std::string m_r_name;
        const std::string m_file_path;
        static const std::string s_scope; // light
        MD5SUM m_key;
        mc::comm::PBLight m_pb_data;
        //
        glm::vec3 m_pos;
        glm::vec3 m_forward;
        glm::vec3 m_color;
        glm::vec3 m_attenuation;
        Kind m_kind; // 光源种类 direction, point, spot
    };
}
#endif