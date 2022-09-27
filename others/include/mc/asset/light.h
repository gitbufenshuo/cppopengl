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
#include <mc/asset/art_logic.h>
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
        void SetCastShadow(bool);
        void CalcLightMat();
        void SetArtLogic(std::shared_ptr<ArtLogic>);
        void UseTexture(int texture_pipe);

        const glm::vec3 &GetPos() const;
        const glm::vec3 &GetForward() const;
        const glm::vec3 &GetColor() const;
        const glm::vec3 &GetAttenuation() const;
        int GetKind() const;
        bool GetCastShadow() const;
        const glm::mat4 &GetLightMat() const;
        unsigned int GetShadowWidth() const;
        unsigned int GetShadowHeight() const;
        unsigned int GetShadowFBO() const;
        unsigned int GetShadowMap() const;
        std::shared_ptr<ArtLogic> GetArtLogic() const;

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
        // shadow
        bool m_cast_shadow{false};     // 是否产生 shadow
        unsigned int m_depthMapFBO{0}; // fbo
        unsigned int m_shadow_map{0};  // texture
        unsigned int m_shadow_width{1024};
        unsigned int m_shadow_height{1024};
        glm::mat4 m_light_mat{1.0f};
        std::shared_ptr<ArtLogic> m_art_logic;
    };
}
#endif