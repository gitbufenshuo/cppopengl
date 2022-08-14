#include <mc/transform.h>

namespace mc::low
{
    Transform::Transform()
    {
    }
    void Transform::SetUpper(Transform *upper)
    {
        m_upper = upper;
    }
    Transform &Transform::GetUpper() const
    {
        return *m_upper;
    }
    const glm::mat4 &Transform::GetMat() const
    {
        return m_model_mat;
    }
}
