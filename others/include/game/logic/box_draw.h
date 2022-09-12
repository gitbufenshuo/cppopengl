#ifndef BOX_DRAW_H
#define BOX_DRAW_H
#include<mc/logic_support.h>
#include <mc/gameobject.h>
namespace game {
    namespace internal
    {
        using Vector3=glm::vec3;
        using Vector4=glm::vec4;
        using Matrix4=glm::mat4;
        /// Intersection test result.
        enum Intersection
        {
            OUTSIDE,
            INTERSECTS,
            INSIDE
        };
        enum FrustumPlane
        {
            PLANE_NEAR = 0,
            PLANE_LEFT,
            PLANE_RIGHT,
            PLANE_UP,
            PLANE_DOWN,
            PLANE_FAR
        };
        static const unsigned NUM_FRUSTUM_PLANES = 6;
        static const unsigned NUM_FRUSTUM_VERTICES = 8;
        inline constexpr float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
        struct Plane{
            Vector3 n;
            float d;
            float Distance(Vector3 point)const{
                return glm::dot(point,n)+d;
            }
            void Define(const Vector3& v0, const Vector3& v1, const Vector3& v2){

           Vector3 dist1 = v1 - v0;
           Vector3 dist2 = v2 - v0;
           Vector3 N= glm::normalize(glm::cross(dist1,dist2));
           n=N;
           d=-glm::dot(n,v0);

            }

        };

        class Frustum
        {
        public:
            Frustum() noexcept = default;

            Frustum(const Frustum &frustum) noexcept{
                *this=frustum;
            }

            Frustum &operator=(const Frustum &rhs) noexcept{
            for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
                planes_[i] = rhs.planes_[i];
            for (unsigned i = 0; i < NUM_FRUSTUM_VERTICES; ++i)
                vertices_[i] = rhs.vertices_[i];
            return *this;
            }

            void Define(float fov, float aspectRatio, float zoom, float nearZ, float farZ, const Matrix4 &transform = Matrix4(1.0f))
            {

                nearZ = std::max(nearZ, 0.0f);
                farZ = std::max(farZ, nearZ);
                float halfViewSize = tanf(fov * M_DEGTORAD_2) / zoom;
                Vector3 near, far;

                near.z= nearZ;
                near.y = near.z * halfViewSize;
                near.x = near.y * aspectRatio;
                far.z = farZ;
                far.y = far.z * halfViewSize;
                far.x = far.y * aspectRatio;

                Define(near, far, transform);
            }

            void Define(const Vector3 &near, const Vector3 &far, const Matrix4 &transform = Matrix4(1.0f))
            {
                

                vertices_[0] = transform * Vector4(near,1.0);
                vertices_[1] = transform * Vector4(near.x, -near.y, near.z,1.0f);
                vertices_[2] = transform * Vector4(-near.x, -near.y, near.z,1.0f);
                vertices_[3] = transform * Vector4(-near.x, near.y, near.z,1.0f);
                vertices_[4] = transform * Vector4(far,1.0);
                vertices_[5] = transform * Vector4(far.x, -far.y, far.z,1.0f);
                vertices_[6] = transform * Vector4(-far.x, -far.y, far.z,1.0f);
                vertices_[7] = transform * Vector4(-far.x, far.y, far.z,1.0f);

                UpdatePlanes();
            }

            void Define(const Matrix4 &projection){
                Matrix4 projInverse = glm::inverse(projection);
                vertices_[0] = projInverse * Vector4(1.0f, 1.0f, 0.0f,1.0f);
                vertices_[1] = projInverse * Vector4(1.0f, -1.0f, 0.0f,1.0f);
                vertices_[2] = projInverse * Vector4(-1.0f, -1.0f, 0.0f,1.0f);
                vertices_[3] = projInverse * Vector4(-1.0f, 1.0f, 0.0f,1.0f);
                vertices_[4] = projInverse * Vector4(1.0f, 1.0f, 1.0f,1.0f);
                vertices_[5] = projInverse * Vector4(1.0f, -1.0f, 1.0f,1.0f);
                vertices_[6] = projInverse * Vector4(-1.0f, -1.0f, 1.0f,1.0f);
                vertices_[7] = projInverse * Vector4(-1.0f, 1.0f, 1.0f,1.0f);
            }

            void DefineSplit(const Matrix4 &projection, float near, float far){
                 Matrix4 projInverse = glm::inverse(projection);

                // Figure out depth values for near & far
                Vector4 nearTemp = projection * Vector4(0.0f, 0.0f, near, 1.0f);
                Vector4 farTemp = projection * Vector4(0.0f, 0.0f, far, 1.0f);
                float nearZ = nearTemp.z / nearTemp.w;
                float farZ = farTemp.z / farTemp.w;

                vertices_[0] = projInverse * Vector4(1.0f, 1.0f, nearZ,1.0f);
                vertices_[1] = projInverse * Vector4(1.0f, -1.0f, nearZ,1.0f);
                vertices_[2] = projInverse * Vector4(-1.0f, -1.0f, nearZ,1.0f);
                vertices_[3] = projInverse * Vector4(-1.0f, 1.0f, nearZ,1.0f);
                vertices_[4] = projInverse * Vector4(1.0f, 1.0f, farZ,1.0f);
                vertices_[5] = projInverse * Vector4(1.0f, -1.0f, farZ,1.0f);
                vertices_[6] = projInverse * Vector4(-1.0f, -1.0f, farZ,1.0f);
                vertices_[7] = projInverse * Vector4(-1.0f, 1.0f, farZ,1.0f);

                UpdatePlanes();
            }

            Intersection IsInside(const Vector3 &point)
            {
                for (const auto &p : planes_)
                {
                    if(p.Distance(point)>0)
                    return OUTSIDE;
                }

                return INSIDE;
            }

            Intersection IsInside(const Vector4 &sphere) const
            {
                bool allInside = true;
                for (const auto &plane : planes_)
                {
                    float dist = plane.Distance({sphere.x,sphere.y,sphere.z});
                    if (dist > sphere.w)
                        return OUTSIDE;
                    else if (dist > -sphere.w)
                        allInside = false;
                }

                return allInside ? INSIDE : INTERSECTS;
            }


            /// Test if a bounding box is inside, outside or intersects.
            Intersection IsInside(const Vector3 &vmin, const Vector3 &vmax) const
            {
                Vector3 center = {(vmin.x+vmax.x)/2,(vmin.y+vmax.y)/2,(vmin.z+vmax.z)/2};
                Vector3 edge = center - vmin;
                bool allInside = true;

                for (const auto &plane : planes_)
                {
                    float dist = plane.Distance(center);
                    Vector3 absNormal={abs(plane.n.x),abs(plane.n.y),abs(plane.n.z)};
                    float absDist = glm::dot(absNormal,edge);

                    if (dist > absDist)
                        return OUTSIDE;
                    else if (dist > -absDist)
                        allInside = false;
                }

                return allInside ? INSIDE : INTERSECTS;
            }
            /// Return distance of a point to the frustum, or 0 if inside.
            float Distance(const Vector3 &point) const
            {
                float distance = 0.0f;
                for (const auto &plane : planes_)
                distance = plane.Distance(point)> distance?plane.Distance(point):distance;
                return distance;
            }

            /// Update the planes. Called internally.
            void UpdatePlanes()
            {
                planes_[PLANE_NEAR].Define(vertices_[2], vertices_[1], vertices_[0]);
                planes_[PLANE_LEFT].Define(vertices_[3], vertices_[7], vertices_[6]);
                planes_[PLANE_RIGHT].Define(vertices_[1], vertices_[5], vertices_[4]);
                planes_[PLANE_UP].Define(vertices_[0], vertices_[4], vertices_[7]);
                planes_[PLANE_DOWN].Define(vertices_[6], vertices_[5], vertices_[1]);
                planes_[PLANE_FAR].Define(vertices_[5], vertices_[6], vertices_[7]);

                // Check if we ended up with inverted planes (reflected transform) and flip in that case
                if (planes_[PLANE_NEAR].Distance(vertices_[5]) < 0.0f)
                {
                    for (auto &plane : planes_)
                    {
                        plane.n= -plane.n;
                        plane.d = -plane.d;
                    }
                }
            }
            Plane planes_[NUM_FRUSTUM_PLANES];
            /// Frustum vertices.
            Vector3 vertices_[NUM_FRUSTUM_VERTICES];
        };
    }
    
    enum class Space : char {
        Local = 1 << 0,
        World = 1 << 1
    };

 

    class Transform {
      private:
        void RecalculateBasis(void);
        void RecalculateEuler(void);

      public:
        glm::vec3 position;
        glm::quat rotation;   
        glm::mat4 transform;  

        float euler_x, euler_y, euler_z;  
        float scale_x, scale_y, scale_z;

        glm::vec3 up;
        glm::vec3 forward;
        glm::vec3 right;

        Transform();

        void Translate(const glm::vec3& vector, Space space = Space::World);
        void Translate(float x, float y, float z, Space space = Space::World);

        void Rotate(const glm::vec3& axis, float angle, Space space);
        void Rotate(const glm::vec3& eulers, Space space);
        void Rotate(float euler_x, float euler_y, float euler_z, Space space);

        void Scale(float scale);
        void Scale(const glm::vec3& scale);
        void Scale(float scale_x, float scale_y, float scale_z);

        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::quat& rotation);
        void SetTransform(const glm::mat4& transform);

        glm::vec3 Local2World(const glm::vec3& v) const;
        glm::vec3 World2Local(const glm::vec3& v) const;

        glm::mat4 GetLocalTransform() const;
        glm::mat4 GetLocalTransform(const glm::vec3& forward, const glm::vec3& up) const;
    };

    class BoxDraw :public mc::low::LogicSupport {   
        public:  
        struct Camera{
            GLFWwindow *window;
            glm::mat4 projection;
            Transform t;
            Camera();
            void Update(float t);
            void ResetView();
            glm::vec2 ConvertScreenToWorld(const glm::vec2& screenPoint);
            glm::vec2 ConvertWorldToScreen(const glm::vec2& worldPoint);
            void BuildProjectionMatrix(float* m, float zBias);
            glm::vec2 m_center;
            float m_zoom;
            int m_width;
            int m_height;
        };
        static Camera g_camera;
        struct GLRenderPoints {
            void create() {
#pragma region 创建着色器程序
                const char* V = \
                    "#version 330\n"
                    "uniform mat4 projectionMatrix;\n"
                    "layout(location = 0) in vec2 v_position;\n"
                    "layout(location = 1) in vec4 v_color;\n"
                    "layout(location = 2) in float v_size;\n"
                    "out vec4 f_color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	f_color = v_color;\n"
                    "	gl_Position = projectionMatrix*vec4(v_position, 0.0f, 1.0f);\n"
                    "   gl_PointSize = v_size;\n"
                    "}\n";

                const char* F = \
                    "#version 330\n"
                    "in vec4 f_color;\n"
                    "out vec4 color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	color = f_color;\n"
                    "}\n";

                unsigned vP = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vP, 1, &V, NULL);
                unsigned fP = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fP, 1, &F, NULL);

                char infolog[512];
                int success;
                glCompileShader(vP);
                glGetShaderiv(vP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "片段着色器编译成功" << std::endl;
                }

                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);

                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);


#pragma endregion

                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0);//位置属性
                glEnableVertexAttribArray(1);//颜色属性	
                glEnableVertexAttribArray(2);//大小属性
                glGenBuffers(3, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[2]);
                glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(size), size, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;


            }
            void Vertex(const glm::vec2& v, const glm::vec4& c, float s) {//在缓冲区中送入一个顶点
                if (m_count == 1024) {	//缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;
                size[m_count] = s;
                m_count++;
            }
            void fflush() {//实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码


                glUseProgram(shader);

                float p[16] = { 0.0 };
                g_camera.BuildProjectionMatrix(p, 0.0);
                glUniformMatrix4fv(projection, 1, GL_FALSE, p);



                glBindVertexArray(vaoId);

                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), color);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[2]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(float), size);

                glEnable(GL_PROGRAM_POINT_SIZE);
                glDrawArrays(GL_POINTS, 0, m_count);
                glDisable(GL_PROGRAM_POINT_SIZE);
                glBindVertexArray(0);
                glUseProgram(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                m_count = 0;
            }
            unsigned int m_count;//点的数目
            unsigned int vaoId;//
            unsigned int bufferId[3];
            unsigned int shader;//着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec2 vertices[maxCount];//位置
            glm::vec4 color[maxCount];//颜色
            float size[maxCount];//大小
            int projection;
        };
        struct GLRenderLines {
            void create() {
#pragma region 创建着色器程序
                const char* V = \
                    "#version 330\n"
                    "uniform mat4 projectionMatrix;\n"
                    "layout(location = 0) in vec3 v_position;\n"
                    "layout(location = 1) in vec4 v_color;\n"
                    "out vec4 f_color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	f_color = v_color;\n"
                    "	gl_Position =projectionMatrix*vec4(v_position, 1.0f);\n"

                    "}\n";

                const char* F = \
                    "#version 330\n"
                    "in vec4 f_color;\n"
                    "out vec4 color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	color = f_color;\n"
                    "}\n";

                unsigned vP = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vP, 1, &V, NULL);
                unsigned fP = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fP, 1, &F, NULL);

                char infolog[512];
                int success;
                glCompileShader(vP);
                glGetShaderiv(vP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "片段着色器编译成功" << std::endl;
                }
                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);
                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);
#pragma endregion
                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0);//位置属性
                glEnableVertexAttribArray(1);//颜色属性	
                glGenBuffers(2, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                m_count = 0;
            }
            void Vertex(const glm::vec3& v, const glm::vec4& c) {//在缓冲区中送入一个顶点
                if (m_count == 1024) {	//缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;
                m_count++;
            }
            void fflush() {//实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码
                glUseProgram(shader);
                float p[16] = { 0.0 };
                g_camera.BuildProjectionMatrix(p, 0.0);
                glUniformMatrix4fv(projection, 1, GL_FALSE, p);
                glBindVertexArray(vaoId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec3), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), color);
                glDrawArrays(GL_LINES, 0, m_count);
                glBindVertexArray(0);
                glUseProgram(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                m_count = 0;
            }
            unsigned int m_count;//点的数目
            unsigned int vaoId;//
            unsigned int bufferId[2];
            unsigned int shader;//着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec3 vertices[maxCount];//位置
            glm::vec4 color[maxCount];//颜色
            int projection;
        };
        struct GLRenderTriangles
        {
            void create() {
#pragma region 创建着色器程序
                const char* V = \
                    "#version 330\n"
                    "uniform mat4 projectionMatrix;\n"
                    "layout(location = 0) in vec3 v_position;\n"
                    "layout(location = 1) in vec4 v_color;\n"
                    "out vec4 f_color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	f_color = v_color;\n"
                    "	gl_Position = projectionMatrix*vec4(v_position, 1.0f);\n"

                    "}\n";

                const char* F = \
                    "#version 330\n"
                    "in vec4 f_color;\n"
                    "out vec4 color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	color = f_color;\n"
                    "}\n";

                unsigned vP = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vP, 1, &V, NULL);
                unsigned fP = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fP, 1, &F, NULL);

                char infolog[512];
                int success;
                glCompileShader(vP);
                glGetShaderiv(vP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "片段着色器编译成功" << std::endl;
                }

                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);

                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);


#pragma endregion

                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0);//位置属性
                glEnableVertexAttribArray(1);//颜色属性	

                glGenBuffers(2, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);


                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;


            }
            void Vertex(const glm::vec3& v, const glm::vec4& c) {//在缓冲区中送入一个顶点
                if (m_count == maxCount) {	//缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;

                m_count++;
            }
            void fflush() {//实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码


                glUseProgram(shader);
                float p[16] = { 0.0 };
                g_camera.BuildProjectionMatrix(p, 0.0);
                glUniformMatrix4fv(projection, 1, GL_FALSE, p);
                glBindVertexArray(vaoId);

                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec3), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), color);


                glDisable(GL_CULL_FACE);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDrawArrays(GL_TRIANGLES, 0, m_count);
                glDisable(GL_BLEND);

                glBindVertexArray(0);
                glUseProgram(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                m_count = 0;
            }
            unsigned int m_count;//点的数目
            unsigned int vaoId;//
            unsigned int bufferId[2];
            unsigned int shader;//着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec3 vertices[maxCount];//位置
            glm::vec4 color[maxCount];//颜色}drawtriangles;
            int projection;
        };
        class DebugDraw
        {
        public:

            DebugDraw();
            ~DebugDraw();

            void Create();
            void Destroy();
            void DrawBound(const glm::vec3& center,const glm::vec3& extent,const glm::vec4& color,bool flag=true);
            void DrawPolygon(const glm::vec3* vertices, int vertexCount, const glm::vec4& color);

            void DrawSolidPolygon(const glm::vec3* vertices, int vertexCount, const glm::vec4& color);

            void DrawCircle(const glm::vec3& center, float radius, const glm::vec3& axis, const glm::vec4& color,bool flag=true);

            void DrawSegment(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color);

            void DrawFrustum(const internal::Frustum& frustum,const glm::vec4& color,bool flag=true)const ;

            void DrawPoint(const glm::vec2& p, float size, const glm::vec4& color);



            void Flush();
        private:
            GLRenderPoints* m_points;
            GLRenderLines* m_lines;
            GLRenderTriangles* m_triangles;

        };
        static DebugDraw maindraw;
    public:
        BoxDraw(mc::low::GameObject *gb);
    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif // !BOX_DRAW_H
