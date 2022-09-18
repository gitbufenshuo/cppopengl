#ifndef MC_CONTAINER_BOUNDING_BOX_H
#define MC_CONTAINER_BOUNDING_BOX_H

#include <limits>

#include <glm/glm.hpp>

namespace mc::container
{
    inline constexpr float M_INFINITY = std::numeric_limits<float>::infinity();
    enum class Intersection
    {
        OUTSIDE,
        INTERSECTS,
        INSIDE
    };

    class BoundingBox
    {
    public:
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;
        using Matrix4 = glm::mat4;

    public:
        BoundingBox() noexcept;
        BoundingBox(const BoundingBox &box) noexcept;
        BoundingBox(const Vector3 &min, const Vector3 &max) noexcept;
        BoundingBox(float min, float max) noexcept;

        BoundingBox &operator=(const BoundingBox &rhs) noexcept;
        bool operator==(const BoundingBox &rhs) const;
        bool operator!=(const BoundingBox &rhs) const;
        void Define(const BoundingBox &box);
        void Define(const Vector3 &min, const Vector3 &max);
        void Define(float min, float max);
        void Define(const Vector3 &point);
        void Merge(const Vector3 &point);
        void Merge(const BoundingBox &box);
        void Define(const Vector3 *vertices, unsigned count);
        void Clear();
        bool Defined() const;
        Vector3 Center() const;
        Vector3 Size() const;
        Vector3 HalfSize() const;
        float DistanceToPoint(const Vector3 &point) const;
        Intersection IsInside(const Vector3 &point) const;
        Intersection IsInside(const BoundingBox &box) const;
        Intersection IsInsideFast(const BoundingBox &box) const;

    private:
        Vector3 min_;
        float dummyMin_{};
        Vector3 max_;
        float dummyMax_{};
    };

}
#endif
