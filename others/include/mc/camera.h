namespace mc::low
{
    class Camera;
}
#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include <glm/glm.hpp>

#include <mc/camera_skybox.h>
#include <mc/transform.h>

namespace mc::low
{
    class Camera
    {
    public:
        Camera();

    public:
        Transform *GetTransform();
        const glm::mat4 &GetViewMat();
        const glm::mat4 &GetProjMat();
        void SetSkybox(Skybox *);
        void DrawSkybox();

    private:
        void updateViewMat();
        void updateProjMat();

    private:
        // view
        std::unique_ptr<Transform> m_transform;
        unsigned int m_camera_version{0};
        glm::mat4 m_view_mat; // view matrix
        // projection
        float m_near{0.1f};
        float m_far{300.0f};
        float m_whr{1.0f};       // width / height
        float m_fov{45.0f};      // fov in degree
        bool m_proj_dirty{true}; // 是否需要更新 m_view_mat
        glm::mat4 m_proj_mat;    // projection matrix
        std::unique_ptr<Skybox> m_skybox{};
    };
}

#endif
