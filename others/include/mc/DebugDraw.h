
#include<mc/engine.h>
struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;

struct Camera
{
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
class DebugDraw 
{
public:
	
	DebugDraw();
	~DebugDraw();

	void Create();
	void Destroy();

	void DrawPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color);

	void DrawSolidPolygon(const glm::vec2* vertices, int vertexCount, const glm::vec4& color) ;

	void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color) ;
	
	
	

	void DrawSolidCircle(const glm::vec2& center, float radius, const glm::vec2& axis, const glm::vec4& color) ;

	void DrawSegment(const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color);

	

	void DrawPoint(const glm::vec2& p, float size, const glm::vec4& color) ;



	void Flush();
private:
	 GLRenderPoints* m_points;
	 GLRenderLines* m_lines;
	 GLRenderTriangles* m_triangles;

};

extern DebugDraw maindraw;
extern Camera g_camera;