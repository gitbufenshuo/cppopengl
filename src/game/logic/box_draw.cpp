#include <iostream>
#include <algorithm>

#include <mc/engine.h>
#include<game/logic/box_draw.h>
namespace game {
    BoxDraw::Camera BoxDraw::g_camera;
    BoxDraw::DebugDraw BoxDraw::maindraw;
    BoxDraw::BoxDraw(mc::low::GameObject *gb): mc::low::LogicSupport{gb}{
        maindraw.Create();
        



    }
    void BoxDraw::Update(double delta_time) {
 
    }
    void BoxDraw::AfterRenderUpdate(double delta_time) {

       std::cout<<"logic update"<<std::endl;
        maindraw.DrawSolidCircle({0,0},10,{1,0},{1.0,0,0,1.0});
        maindraw.Flush();
        std::cout<<"end logic update"<<std::endl;

    }
    void BoxDraw::BeforeRenderUpdate(double delta_time) {

    }
    BoxDraw::DebugDraw::DebugDraw()
    {
        m_lines = nullptr;
        m_triangles = nullptr;
        m_points = nullptr;
    }

    BoxDraw::DebugDraw::~DebugDraw()
    {
    }

    void BoxDraw::DebugDraw::Create()
    {
        this->m_points = new GLRenderPoints();
        this->m_lines = new GLRenderLines();
        this->m_triangles = new GLRenderTriangles();
        this->m_points->create();
        this->m_lines->create();
        this->m_triangles->create();
    }

    void BoxDraw::DebugDraw::Destroy()
    {
        if (m_points != nullptr)
            delete m_points;
        m_points = nullptr;
        if (m_lines != nullptr)
            delete m_lines;
        m_lines = nullptr;
        if (m_triangles != nullptr)
            delete m_triangles;
        m_triangles = nullptr;
    }

    void BoxDraw::DebugDraw::DrawPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color)
    {
        const glm::vec2* p2 = vertices + (vertexCount - 1);
        for (int i = 0; i < vertexCount; i++) {
            m_lines->Vertex(*(vertices + i), color);
            m_lines->Vertex(*p2, color);
            p2 = vertices + i;
        }
    }

    void BoxDraw::DebugDraw::DrawSolidPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color)
    {
        glm::vec4 fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        for (int i = 1; i < vertexCount - 1; i++) {
            m_triangles->Vertex(*vertices, fillColor);
            m_triangles->Vertex(*(vertices + i), fillColor);
            m_triangles->Vertex(*(vertices + i + 1), fillColor);
        }

        const glm::vec2* p2 = vertices + (vertexCount - 1);
        for (int i = 0; i < vertexCount; i++) {
            m_lines->Vertex(*(vertices + i), color);
            m_lines->Vertex(*p2, color);
            p2 = vertices + i;
        }
    }

    void BoxDraw::DebugDraw::DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color)
    {
        float d = 2 * 3.14 / 32;
        float sind = sinf(d);
        float cosd = cosf(d);
        glm::vec2 start = radius * glm::vec2(0.0, 1.0);
        for (int i = 0; i < 32; i++) {
            glm::vec2 next = { cosd * start.x - sind * start.y,sind * start.x + cosd * start.y };
            m_lines->Vertex(center + start, color);
            m_lines->Vertex(center + next, color);
            start = next;
        }
    }

    void BoxDraw::DebugDraw::DrawSolidCircle(const glm::vec2& center, float radius, const glm::vec2& axis, const glm::vec4& color)
    {
        float d = 2 * 3.14 / 32;
        float sind = sinf(d);
        float cosd = cosf(d);
        glm::vec2 start = radius * glm::vec2(0.0, 1.0);
        glm::vec4 c = { color.r / 2,color.g / 2,color.b / 2,color.a / 2 };
        for (int i = 0; i < 32; i++) {
            glm::vec2 next = { cosd * start.x - sind * start.y,sind * start.x + cosd * start.y };
            m_triangles->Vertex(center + start, c);
            m_triangles->Vertex(center + next, c);
            m_triangles->Vertex(center, c);
            start = next;
        }
        DrawCircle(center, radius, color);
        m_lines->Vertex(center, color);
        m_lines->Vertex(center + radius * axis, color);
    }

    void BoxDraw::DebugDraw::DrawSegment(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color)
    {
        m_lines->Vertex(p1, color);
        m_lines->Vertex(p2, color);
    }



    void BoxDraw::DebugDraw::DrawPoint(const glm::vec2& p, float size, const glm::vec4& color)
    {
        m_points->Vertex(p, color, size);
    }



    void BoxDraw::DebugDraw::Flush()
    {
        m_lines->fflush();
        m_triangles->fflush();
        m_points->fflush();
    }
    BoxDraw::Camera::Camera()
    {
        m_width = 800;
        m_height = 800;
        ResetView();
    }

    void BoxDraw::Camera::ResetView()
    {
        m_center = { 0.0f, 0.0f };
        m_zoom = 1.0f;
    }
    //相机上的屏幕对应于世界空间的一块矩形区域
    glm::vec2 BoxDraw::Camera::ConvertScreenToWorld(const glm::vec2& ps)
    {

        float w = float(m_width);
        float h = float(m_height);
        float u = ps.x / w;
        float v = (h - ps.y) / h;

        float ratio = w / h;
        glm::vec2 extents(ratio * 25.0f, 25.0f);
        extents *= m_zoom;

        glm::vec2 lower = m_center - extents;
        glm::vec2 upper = m_center + extents;

        glm::vec2 pw;
        pw.x = (1.0f - u) * lower.x + u * upper.x;//插值算法
        pw.y = (1.0f - v) * lower.y + v * upper.y;
        return pw;
    }

    glm::vec2 BoxDraw::Camera::ConvertWorldToScreen(const glm::vec2& pw)
    {

        float w = float(m_width);
        float h = float(m_height);
        float ratio = w / h;
        glm::vec2 extents(ratio * 25.0f, 25.0f);
        extents *= m_zoom;

        glm::vec2 lower = m_center - extents;
        glm::vec2 upper = m_center + extents;

        float u = (pw.x - lower.x) / (upper.x - lower.x);
        float v = (pw.y - lower.y) / (upper.y - lower.y);

        glm::vec2 ps;
        ps.x = u * w;
        ps.y = (1.0f - v) * h;
        return ps;
    }

    void BoxDraw::Camera::BuildProjectionMatrix(float* m, float zBias)
    {
        float w = float(m_width);
        float h = float(m_height);
        float ratio = w / h;
        glm::vec2 extents(ratio * 25.0f, 25.0f);
        extents *= m_zoom;

        glm::vec2 lower = m_center - extents;
        glm::vec2 upper = m_center + extents;

        m[0] = 2.0f / (upper.x - lower.x);
        m[1] = 0.0f;
        m[2] = 0.0f;
        m[3] = 0.0f;

        m[4] = 0.0f;
        m[5] = 2.0f / (upper.y - lower.y);
        m[6] = 0.0f;
        m[7] = 0.0f;

        m[8] = 0.0f;
        m[9] = 0.0f;
        m[10] = 1.0f;
        m[11] = 0.0f;

        m[12] = -(upper.x + lower.x) / (upper.x - lower.x);
        m[13] = -(upper.y + lower.y) / (upper.y - lower.y);
        m[14] = zBias;
        m[15] = 1.0f;
    }


}