#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <mc/engine.h>
#include<game/logic/box_draw.h>


namespace game {
   

    void CreateSphere(float radius = 1.0f);
    void CreateCube(float size = 1.0f);
    void CreatePlane(float size = 10.0f);
    void Create2DQuad(float size = 1.0f);
    void CreateTorus(float R = 1.5f, float r = 0.5f);
    void CreateCapsule(float a = 2.0f, float r = 1.0f);
    void CreatePyramid(float s = 2.0f);

    BoxDraw::Camera BoxDraw::g_camera;
    BoxDraw::DebugDraw BoxDraw::maindraw;
    BoxDraw::BoxDraw(mc::low::GameObject *gb): mc::low::LogicSupport{gb}{
        maindraw.Create();
    }
    void BoxDraw::Update(double delta_time) {
        static float angle=0;
        angle+=delta_time*3.14;
        g_camera.Update(delta_time);
        maindraw.DrawCircle({0,0,-30},10,{cos(angle),1,sin(angle)},{1.0,0,0,1.0});
        maindraw.DrawBound({0,0,-30},{1,2,3},{0,1,0,1});
        internal::Frustum Fr;
        Fr.Define(45,1,1,1.0,10.0);
        auto it=Fr.IsInside({0,0,0},{10,10,10});
        if(it==internal::Intersection::INTERSECTS)
        maindraw.DrawFrustum(Fr,{1.0,0.0,1.0,1.0});
        else
        maindraw.DrawFrustum(Fr,{1.0,1.0,0.0,1.0});
        maindraw.DrawBound({5,5,5},{5,5,5},{0,1,0,1});
    }
    void BoxDraw::AfterRenderUpdate(double delta_time) {
      
        maindraw.Flush();
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

    void BoxDraw::DebugDraw::DrawPolygon(const glm::vec3* vertices, int vertexCount, const glm::vec4& color)
    {
        const glm::vec3* p2 = vertices + (vertexCount - 1);
        for (int i = 0; i < vertexCount; i++) {
            m_lines->Vertex(*(vertices + i), color);
            m_lines->Vertex(*p2, color);
            p2 = vertices + i;
        }
    }

    void BoxDraw::DebugDraw::DrawSolidPolygon(const glm::vec3* vertices, int vertexCount, const glm::vec4& color)
    {
        glm::vec4 fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        for (int i = 1; i < vertexCount - 1; i++) {
            m_triangles->Vertex(*vertices, fillColor);
            m_triangles->Vertex(*(vertices + i), fillColor);
            m_triangles->Vertex(*(vertices + i + 1), fillColor);
        }

        const glm::vec3* p2 = vertices + (vertexCount - 1);
        for (int i = 0; i < vertexCount; i++) {
            m_lines->Vertex(*(vertices + i), color);
            m_lines->Vertex(*p2, color);
            p2 = vertices + i;
        }
    }
    
    void BoxDraw::DebugDraw::DrawBound(const glm::vec3& center,const glm::vec3& extent,const glm::vec4& color,bool flag){
        static const glm::vec3 data[]={
            {-1.0f, -1.0f, -1.0f},{-1.0f, -1.0f, +1.0f},{+1.0f, -1.0f, +1.0f},{+1.0f, -1.0f, -1.0f},
            {-1.0f, +1.0f, -1.0f},{-1.0f, +1.0f, +1.0f},{+1.0f, +1.0f, +1.0f},{+1.0f, +1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},{-1.0f, +1.0f, -1.0f},{ +1.0f, +1.0f, -1.0f},{+1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, +1.0f},{-1.0f, +1.0f, +1.0f},{+1.0f, +1.0f, +1.0f},{+1.0f, -1.0f, +1.0f},
            {-1.0f, -1.0f, -1.0f},{-1.0f, -1.0f, +1.0f},{-1.0f, +1.0f, +1.0f},{-1.0f, +1.0f, -1.0f},  
            {+1.0f, -1.0f, -1.0f},{+1.0f, -1.0f, +1.0f},{+1.0f, +1.0f, +1.0f},{+1.0f, +1.0f, -1.0f}    
        };
        static const int indices[]= {
            +0, +2, +1,   +0, +3, +2,   +4, +5, +6,
            +4, +6, +7,   +8, +9, 10,   +8, 10, 11,
            12, 15, 14,   12, 14, 13,   16, 17, 18,
            16, 18, 19,   20, 23, 22,   20, 22, 21
        };
        glm::vec4 c = { color.r / 2,color.g / 2,color.b / 2,color.a / 2 };
        for(size_t i=0;i<12;i++){
            m_triangles->Vertex(center+data[indices[3*i]]*extent,c);
            m_triangles->Vertex(center+data[indices[3*i+1]]*extent,c);
            m_triangles->Vertex(center+data[indices[3*i+2]]*extent,c);
            if(flag){
                m_lines->Vertex(center+data[indices[3*i]]*extent,color);
                m_lines->Vertex(center+data[indices[3*i+1]]*extent,color);

                m_lines->Vertex(center+data[indices[3*i+1]]*extent,color);
                m_lines->Vertex(center+data[indices[3*i+2]]*extent,color);

                m_lines->Vertex(center+data[indices[3*i+2]]*extent,color);
                m_lines->Vertex(center+data[indices[3*i]]*extent,color);
            }
        }
    }

    void BoxDraw::DebugDraw::DrawCircle(const glm::vec3& center, float radius, const glm::vec3& axis, const glm::vec4& color,bool flag)
    {
        float d = 2 * 3.141592654 / 32;
        float sind = sinf(d);
        float cosd = cosf(d);
        glm::vec2 start = radius * glm::vec2(0.0, 1.0);
        auto zaxis= glm::cross(axis,glm::vec3(0,1,0));
        auto yaxis= glm::cross(zaxis,axis);
        yaxis=glm::normalize(yaxis);
        auto xaxis=glm::normalize(axis);
        glm::vec4 c = { color.r / 2,color.g / 2,color.b / 2,color.a / 2 };
        for (int i = 0; i < 32; i++) {
            glm::vec2 next = { cosd * start.x - sind * start.y,sind * start.x + cosd * start.y };
            if(flag){
            m_triangles->Vertex(center + start.x*xaxis+start.y*yaxis, c);
            m_triangles->Vertex(center + next.x*xaxis+next.y*yaxis, c);
            m_triangles->Vertex(center, c);
            }
            m_lines->Vertex(center + start.x*xaxis+start.y*yaxis, color);
            m_lines->Vertex(center + next.x*xaxis+next.y*yaxis, color);
            start = next;
        }

       m_lines->Vertex(center, color);
       m_lines->Vertex(center + radius * xaxis, color);
    }
    void BoxDraw::DebugDraw::DrawFrustum(const internal::Frustum& frustum,const glm::vec4& color,bool flag)const {
        static const int indices[] = {
            0, 2, 1, 0, 3, 2, 3, 4, 7,
            3, 0, 4, 6, 5, 2, 2, 5, 1,
            5, 6, 7, 5, 7, 4, 6, 3, 7,
            6, 2, 3, 0, 1, 5, 4, 0, 5};
        for (size_t i = 0; i < 4; i++)
        {

            m_lines->Vertex(frustum.vertices_[i], color);
            m_lines->Vertex(frustum.vertices_[(i + 1) % 4], color);

            m_lines->Vertex(frustum.vertices_[i + 4], color);
            m_lines->Vertex(frustum.vertices_[(i + 1) % 4 + 4], color);

            m_lines->Vertex(frustum.vertices_[i], color);
            m_lines->Vertex(frustum.vertices_[i + 4], color);

      }
      if(flag){
        glm::vec4 c={color.r/2,color.g/2,color.b/2,color.a/2};
        for(size_t i=0;i<12;i++){

            m_triangles->Vertex(frustum.vertices_[indices[3*i]],c);
            m_triangles->Vertex(frustum.vertices_[indices[3*i+1]],c);
            m_triangles->Vertex(frustum.vertices_[indices[3*i+2]],c);
        }


      }
        

    }
    void BoxDraw::DebugDraw::DrawSegment(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color)
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
        projection=glm::perspectiveFovRH((float)glm::radians(45.0f),1600.0f,900.0f,0.1f,100.0f);
        m_width = 1600;
        m_height = 900;
        ResetView();
    }

    void BoxDraw::Camera::ResetView()
    {
        m_center = { 0.0f, 0.0f };
        m_zoom = 1.0f;
    }

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
        auto it=this->projection*t.GetLocalTransform();
        memcpy(m,&it[0][0],sizeof(it));


    }
    void BoxDraw::Camera::Update(float delta_time){
        static float speed=6;
       if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            // A key
              t.Translate({-delta_time*speed,0,0},Space::Local);      
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        { 
            // D key
              t.Translate({delta_time*speed,0,0},Space::Local);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            // W key
              t.Translate({0,0,-delta_time*speed},Space::Local);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            // S key
              t.Translate({0,0,delta_time*speed},Space::Local);
        }
        static double x = -1, y = -1;
        static double prex = -1, prey = -1;
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            glfwGetCursorPos(window, &x, &y);
            if (prex >= 0) {
               auto anglex=-(x - prex)*45.0f*delta_time;
               auto angley=-(y - prey)*20.0f*delta_time;
               t.Rotate({0,1,0},anglex,Space::Local);
               t.Rotate({1,0,0},angley,Space::Local);
            }
            prex = x;
            prey = y;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            prex = prey = -1;
        }
    }
    static constexpr glm::vec3 origin        { 0.0f };
    static constexpr glm::mat4 identity      { 1.0f };
    static constexpr glm::quat eye           { 1.0f, 0.0f, 0.0f, 0.0f };  // wxyz
    static constexpr glm::vec3 world_right   { 1.0f, 0.0f, 0.0f };  // +x axis
    static constexpr glm::vec3 world_up      { 0.0f, 1.0f, 0.0f };  // +y axis
    static constexpr glm::vec3 world_forward { 0.0f, 0.0f,-1.0f };  // -z axis
    Transform::Transform() :
        transform(identity), position(origin), rotation(eye),
        right(world_right), up(world_up), forward(world_forward),
        euler_x(0.0f), euler_y(0.0f), euler_z(0.0f),
        scale_x(1.0f), scale_y(1.0f), scale_z(1.0f) {}

    void Transform::Translate(const glm::vec3& vector, Space space) {
        if (space == Space::Local) {
            glm::vec3 world_v = Local2World(vector);
            this->position += world_v;
            this->transform[3] = glm::vec4(position, 1.0f);
        }
        else {
            this->position += vector;
            this->transform[3] = glm::vec4(position, 1.0f);
        }
    }

    void Transform::Translate(float x, float y, float z, Space space) {
        Translate(glm::vec3(x, y, z), space);
    }

    void Transform::Rotate(const glm::vec3& axis, float angle, Space space) {
        float radians = glm::radians(angle);
        glm::vec3 v = glm::normalize(axis);

        glm::mat4 R = glm::rotate(radians, v);     
        glm::quat Q = glm::angleAxis(radians, v);  

        if (space == Space::Local) {
            this->transform = this->transform * R;
            this->rotation = glm::normalize(this->rotation * Q);
        }
        else {
            this->transform = R * this->transform;
            this->rotation = glm::normalize(Q * this->rotation);
            this->position = glm::vec3(this->transform[3]);
        }

        RecalculateEuler();
        RecalculateBasis();
    }

    void Transform::Rotate(const glm::vec3& eulers, Space space) {
        glm::vec3 radians = glm::radians(eulers);
        glm::mat4 RX = glm::rotate(radians.x, world_right);
        glm::mat4 RY = glm::rotate(radians.y, world_up);
        glm::mat4 RZ = glm::rotate(radians.z, world_forward);
        glm::mat4 R = RZ * RX * RY;  

        glm::quat QX = glm::angleAxis(radians.x, world_right);
        glm::quat QY = glm::angleAxis(radians.y, world_up);
        glm::quat QZ = glm::angleAxis(radians.z, world_forward);
        glm::quat Q = QZ * QX * QY;  

        if (space == Space::Local) {
            this->transform = this->transform * R;
            this->rotation = glm::normalize(this->rotation * Q);
        }
        else {
            this->transform = R * this->transform;
            this->rotation = glm::normalize(Q * this->rotation);
            this->position = glm::vec3(this->transform[3]);
        }

        RecalculateEuler();
        RecalculateBasis();
    }

    void Transform::Rotate(float euler_x, float euler_y, float euler_z, Space space) {
        Rotate(glm::vec3(euler_x, euler_y, euler_z), space);
    }

    void Transform::Scale(float scale) {
        this->transform = glm::scale(this->transform, glm::vec3(scale));
        this->scale_x *= scale;
        this->scale_y *= scale;
        this->scale_z *= scale;
    }

    void Transform::Scale(const glm::vec3& scale) {
        this->transform = glm::scale(this->transform, scale);
        this->scale_x *= scale.x;
        this->scale_y *= scale.y;
        this->scale_z *= scale.z;
    }

    void Transform::Scale(float scale_x, float scale_y, float scale_z) {
        Scale(glm::vec3(scale_x, scale_y, scale_z));
    }

    void Transform::SetPosition(const glm::vec3& position) {
        this->position = position;
        this->transform[3] = glm::vec4(position, 1.0f);
    }

    void Transform::SetRotation(const glm::quat& rotation) {
        glm::vec4 T = this->transform[3]; 
        this->transform = glm::mat4(1.0f);
        this->transform[0][0] = scale_x;
        this->transform[1][1] = scale_y;
        this->transform[2][2] = scale_z;
        this->transform[3][3] = 1;
        this->rotation = glm::normalize(rotation);
        this->transform = glm::mat4_cast(this->rotation) * this->transform;  
        this->transform[3] = T;  
        RecalculateEuler();
        RecalculateBasis();
    }

    void Transform::SetTransform(const glm::mat4& transform) {
        this->scale_x = glm::length(transform[0]);
        this->scale_y = glm::length(transform[1]);
        this->scale_z = glm::length(transform[2]);
        glm::mat3 pure_rotation_matrix = glm::mat3(
            transform[0] / scale_x,  // glm::normalize
            transform[1] / scale_y,  // glm::normalize
            transform[2] / scale_z   // glm::normalize
        );
        this->transform = transform;
        this->position = glm::vec3(transform[3]);
        this->rotation = glm::normalize(glm::quat_cast(pure_rotation_matrix));
        RecalculateEuler();
        RecalculateBasis();
    }

    void Transform::RecalculateBasis() {
        this->right   = glm::normalize(glm::vec3(this->transform[0]));
        this->up      = glm::normalize(glm::vec3(this->transform[1]));
        this->forward = glm::normalize(glm::vec3(this->transform[2])) * (-1.0f);
    }

    void Transform::RecalculateEuler() {
        glm::vec3 eulers = glm::eulerAngles(this->rotation);
        this->euler_x = glm::degrees(eulers.x);
        this->euler_y = glm::degrees(eulers.y);
        this->euler_z = glm::degrees(eulers.z);
    }

    glm::vec3 Transform::Local2World(const glm::vec3& v) const {
        return this->rotation * v;
    }

    glm::vec3 Transform::World2Local(const glm::vec3& v) const {
        return glm::inverse(this->rotation) * v;
    }

    glm::mat4 Transform::GetLocalTransform() const {
        return glm::lookAt(position, position + forward, up);
    }

    glm::mat4 Transform::GetLocalTransform(const glm::vec3& forward, const glm::vec3& up) const {
        return glm::lookAt(position, position + forward, up);
    }
        void CreateSphere(float radius ){

        }
        void CreateCube(float size ){
        constexpr int n_vertices = 24;  
        constexpr int stride = 8;  // 3 + 3 + 2

        std::vector<glm::vec3> vertices;
        vertices.reserve(n_vertices);

        static const float data[] = {

            -1.0f, -1.0f, -1.0f,   +0.0f, -1.0f, +0.0f,   0.0f, 0.0f,
            -1.0f, -1.0f, +1.0f,   +0.0f, -1.0f, +0.0f,   0.0f, 1.0f,
            +1.0f, -1.0f, +1.0f,   +0.0f, -1.0f, +0.0f,   1.0f, 1.0f,
            +1.0f, -1.0f, -1.0f,   +0.0f, -1.0f, +0.0f,   1.0f, 0.0f,
            -1.0f, +1.0f, -1.0f,   +0.0f, +1.0f, +0.0f,   1.0f, 0.0f,
            -1.0f, +1.0f, +1.0f,   +0.0f, +1.0f, +0.0f,   1.0f, 1.0f,
            +1.0f, +1.0f, +1.0f,   +0.0f, +1.0f, +0.0f,   0.0f, 1.0f,
            +1.0f, +1.0f, -1.0f,   +0.0f, +1.0f, +0.0f,   0.0f, 0.0f,
            -1.0f, -1.0f, -1.0f,   +0.0f, +0.0f, -1.0f,   0.0f, 0.0f,
            -1.0f, +1.0f, -1.0f,   +0.0f, +0.0f, -1.0f,   0.0f, 1.0f,
            +1.0f, +1.0f, -1.0f,   +0.0f, +0.0f, -1.0f,   1.0f, 1.0f,
            +1.0f, -1.0f, -1.0f,   +0.0f, +0.0f, -1.0f,   1.0f, 0.0f,
            -1.0f, -1.0f, +1.0f,   +0.0f, +0.0f, +1.0f,   0.0f, 0.0f,
            -1.0f, +1.0f, +1.0f,   +0.0f, +0.0f, +1.0f,   0.0f, 1.0f,
            +1.0f, +1.0f, +1.0f,   +0.0f, +0.0f, +1.0f,   1.0f, 1.0f,
            +1.0f, -1.0f, +1.0f,   +0.0f, +0.0f, +1.0f,   1.0f, 0.0f,
            -1.0f, -1.0f, -1.0f,   -1.0f, +0.0f, +0.0f,   0.0f, 0.0f,
            -1.0f, -1.0f, +1.0f,   -1.0f, +0.0f, +0.0f,   0.0f, 1.0f,
            -1.0f, +1.0f, +1.0f,   -1.0f, +0.0f, +0.0f,   1.0f, 1.0f,
            -1.0f, +1.0f, -1.0f,   -1.0f, +0.0f, +0.0f,   1.0f, 0.0f,
            +1.0f, -1.0f, -1.0f,   +1.0f, +0.0f, +0.0f,   0.0f, 0.0f,
            +1.0f, -1.0f, +1.0f,   +1.0f, +0.0f, +0.0f,   0.0f, 1.0f,
            +1.0f, +1.0f, +1.0f,   +1.0f, +0.0f, +0.0f,   1.0f, 1.0f,
            +1.0f, +1.0f, -1.0f,   +1.0f, +0.0f, +0.0f,   1.0f, 0.0f
        };

        for (unsigned int i = 0; i < n_vertices; i++) {
            unsigned int offset = i * stride;
            vertices.push_back(glm::vec3(data[offset + 0], data[offset + 1], data[offset + 2]) * size);
        }

        // counter-clockwise winding order
        std::vector<GLuint> indices {
            +0, +2, +1,   +0, +3, +2,   +4, +5, +6,
            +4, +6, +7,   +8, +9, 10,   +8, 10, 11,
            12, 15, 14,   12, 14, 13,   16, 17, 18,
            16, 18, 19,   20, 23, 22,   20, 22, 21
        };


        }
        void CreatePlane(float size ){

        }
        void Create2DQuad(float size ){

        }
        void CreateTorus(float R , float r ){

        }
        void CreateCapsule(float a , float r){

        }
        void CreatePyramid(float s){

        }

}