#ifndef BOX_DRAW_H
#define BOX_DRAW_H
#include<mc/logic_support.h>
#include <mc/gameobject.h>
namespace game {
    class BoxDraw :public mc::low::LogicSupport {   
        public:  
        
     
        struct Camera{
            Camera();

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
            glm::vec2 vertices[1024];//位置
            glm::vec4 color[1024];//颜色
            float size[1024];//大小
            int projection;
        };
        struct GLRenderLines {
            void create() {
#pragma region 创建着色器程序
                const char* V = \
                    "#version 330\n"
                    "uniform mat4 projectionMatrix;\n"
                    "layout(location = 0) in vec2 v_position;\n"
                    "layout(location = 1) in vec4 v_color;\n"
                    "out vec4 f_color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	f_color = v_color;\n"
                    "	gl_Position =projectionMatrix*vec4(v_position, 0.0f, 1.0f);\n"

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
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);


                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;


            }
            void Vertex(const glm::vec2& v, const glm::vec4& c) {//在缓冲区中送入一个顶点
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
               std::cout<<"begin line draw :"<<m_count<<std::endl;

                glUseProgram(shader);


                float p[16] = { 0.0 };
                g_camera.BuildProjectionMatrix(p, 0.0);
                glUniformMatrix4fv(projection, 1, GL_FALSE, p);
                glBindVertexArray(vaoId);

                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), vertices);
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
            glm::vec2 vertices[1024];//位置
            glm::vec4 color[1024];//颜色
            int projection;
        };
        struct GLRenderTriangles
        {
            void create() {
#pragma region 创建着色器程序
                const char* V = \
                    "#version 330\n"
                    "uniform mat4 projectionMatrix;\n"
                    "layout(location = 0) in vec2 v_position;\n"
                    "layout(location = 1) in vec4 v_color;\n"
                    "out vec4 f_color;\n"
                    "void main(void)\n"
                    "{\n"
                    "	f_color = v_color;\n"
                    "	gl_Position = projectionMatrix*vec4(v_position, 0.0f, 1.0f);\n"

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
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);


                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;


            }
            void Vertex(const glm::vec2& v, const glm::vec4& c) {//在缓冲区中送入一个顶点
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
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec2), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_count * sizeof(glm::vec4), color);



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
            glm::vec2 vertices[maxCount];//位置
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

            void DrawPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color);

            void DrawSolidPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color);

            void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color);




            void DrawSolidCircle(const glm::vec2& center, float radius, const glm::vec2& axis, const glm::vec4& color);

            void DrawSegment(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color);



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
