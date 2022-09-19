#include <mc/container/box2d.h>

namespace mc::container
{

    glm::vec2 Box2D::GetLeftBottom() const
    {
        return m_left_bottom;
    }

    glm::vec2 Box2D::GetSize() const
    {
        return m_size;
    }

    glm::vec2 Box2D::GetCenter() const
    {
        return glm::vec2{
            m_left_bottom.x + m_size.x / 2,
            m_left_bottom.y + m_size.y / 2,
        };
    }

    glm::vec2 Box2D::GetRightTop() const
    {
        return glm::vec2{m_left_bottom.x + m_size.x, m_left_bottom.y + m_size.y};
    }
    float Box2D::GetRight() const
    {
        return m_left_bottom.x + m_size.x;
    }
    float Box2D::GetLeft() const
    {
        return m_left_bottom.x;
    }
    float Box2D::GetBottom() const
    {
        return m_left_bottom.y;
    }
    float Box2D::GetTop() const
    {
        return m_left_bottom.x + m_size.y;
    }

    Box2D::Box2D(glm::vec2 left_bottom, glm::vec2 size) : m_left_bottom{left_bottom}, m_size{size}
    {
    }
    bool Box2D::Contains(const Box2D &other)
    {
        return m_left_bottom.x <= other.m_left_bottom.x &&
               m_left_bottom.y <= other.m_left_bottom.y &&
               m_size.x >= other.m_size.x &&
               m_size.y >= other.m_size.y;
    }
    bool Box2D::Intersects(const Box2D &other)
    {
        return !(GetRight() < other.GetLeft() ||
                 GetLeft() > other.GetRight() ||
                 GetBottom() > other.GetTop() ||
                 GetTop() < other.GetBottom());
    }

}