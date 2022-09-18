#include <mc/container/bounding_box.h>

namespace mc::container
{
    BoundingBox::BoundingBox() noexcept : min_(M_INFINITY, M_INFINITY, M_INFINITY),
                                          max_(-M_INFINITY, -M_INFINITY, -M_INFINITY)
    {
    }
    BoundingBox::BoundingBox(const BoundingBox &box) noexcept : min_(box.min_),
                                                                max_(box.max_)
    {
    }
    BoundingBox::BoundingBox(const Vector3 &min, const Vector3 &max) noexcept : min_(min),
                                                                                max_(max)
    {
    }

    BoundingBox::BoundingBox(float min, float max) noexcept : min_(Vector3(min, min, min)),
                                                              max_(Vector3(max, max, max))
    {
    }

    BoundingBox &BoundingBox::operator=(const BoundingBox &rhs) noexcept
    {
        min_ = rhs.min_;
        max_ = rhs.max_;
        return *this;
    }
    bool BoundingBox::operator==(const BoundingBox &rhs) const { return (min_ == rhs.min_ && max_ == rhs.max_); }
    bool BoundingBox::operator!=(const BoundingBox &rhs) const { return (min_ != rhs.min_ || max_ != rhs.max_); }
    void BoundingBox::Define(const BoundingBox &box)
    {
        Define(box.min_, box.max_);
    }
    void BoundingBox::Define(const Vector3 &min, const Vector3 &max)
    {
        min_ = min;
        max_ = max;
    }
    void BoundingBox::Define(float min, float max)
    {
        min_ = Vector3(min, min, min);
        max_ = Vector3(max, max, max);
    }
    void BoundingBox::Define(const Vector3 &point)
    {
        min_ = max_ = point;
    }
    void BoundingBox::Merge(const Vector3 &point)
    {

        if (point.x < min_.x)
            min_.x = point.x;
        if (point.y < min_.y)
            min_.y = point.y;
        if (point.z < min_.z)
            min_.z = point.z;
        if (point.x > max_.x)
            max_.x = point.x;
        if (point.y > max_.y)
            max_.y = point.y;
        if (point.z > max_.z)
            max_.z = point.z;
    }
    void BoundingBox::Merge(const BoundingBox &box)
    {

        if (box.min_.x < min_.x)
            min_.x = box.min_.x;
        if (box.min_.y < min_.y)
            min_.y = box.min_.y;
        if (box.min_.z < min_.z)
            min_.z = box.min_.z;
        if (box.max_.x > max_.x)
            max_.x = box.max_.x;
        if (box.max_.y > max_.y)
            max_.y = box.max_.y;
        if (box.max_.z > max_.z)
            max_.z = box.max_.z;
    }
    void BoundingBox::Define(const Vector3 *vertices, unsigned count)
    {
        Clear();
        for (size_t i = 0; i < count; i++)
        {
            Merge(vertices[i]);
        }
    }
    void BoundingBox::Clear()
    {
        min_ = Vector3(M_INFINITY, M_INFINITY, M_INFINITY);
        max_ = Vector3(-M_INFINITY, -M_INFINITY, -M_INFINITY);
    }
    bool BoundingBox::Defined() const
    {
        return min_.x != M_INFINITY;
    }
    BoundingBox::Vector3 BoundingBox::Center() const { return (max_ + min_) * 0.5f; }
    BoundingBox::Vector3 BoundingBox::Size() const { return max_ - min_; }
    BoundingBox::Vector3 BoundingBox::HalfSize() const { return (max_ - min_) * 0.5f; }
    float BoundingBox::DistanceToPoint(const Vector3 &point) const
    {
        const Vector3 offset = Center() - point;
        const Vector3 absOffset(abs(offset.x), abs(offset.y), abs(offset.z));
        return glm::max({0, 0, 0}, absOffset - HalfSize()).length();
    }
    Intersection BoundingBox::IsInside(const Vector3 &point) const
    {
        if (point.x < min_.x || point.x > max_.x || point.y < min_.y || point.y > max_.y ||
            point.z < min_.z || point.z > max_.z)
            return Intersection::OUTSIDE;
        else
            return Intersection::INSIDE;
    }
    Intersection BoundingBox::IsInside(const BoundingBox &box) const
    {
        if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
            box.max_.z < min_.z || box.min_.z > max_.z)
            return Intersection::OUTSIDE;
        else if (box.min_.x < min_.x || box.max_.x > max_.x || box.min_.y < min_.y || box.max_.y > max_.y ||
                 box.min_.z < min_.z || box.max_.z > max_.z)
            return Intersection::INTERSECTS;
        else
            return Intersection::INSIDE;
    }
    Intersection BoundingBox::IsInsideFast(const BoundingBox &box) const
    {
        if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
            box.max_.z < min_.z || box.min_.z > max_.z)
            return Intersection::OUTSIDE;
        else
            return Intersection::INSIDE;
    }
}