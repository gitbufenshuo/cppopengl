#ifndef MC_CONTAINER_BOX2D_H
#define MC_CONTAINER_BOX2D_H

#include <glm/glm.hpp>

namespace mc::container
{
    class Box2D
    {
    public:
        Box2D(glm::vec2 left_bottom = glm::vec2{0, 0}, glm::vec2 size = glm::vec2{0, 0});

    public:
        glm::vec2 GetLeftBottom() const;
        glm::vec2 GetSize() const;
        glm::vec2 GetCenter() const;
        glm::vec2 GetRightTop() const;
        float GetRight() const;
        float GetLeft() const;
        float GetBottom() const;
        float GetTop() const;
        bool Contains(const Box2D &other);   // 是否完全包含
        bool Intersects(const Box2D &other); // 是否重叠
    private:
        glm::vec2 m_left_bottom{}; // 左下角 xy 坐标
        glm::vec2 m_size{};        // 宽x 高y
    };
}
#endif