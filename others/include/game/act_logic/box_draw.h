#ifndef BOX_DRAW_H
#define BOX_DRAW_H

#include <mc/gameobject.h>

#include <mc/asset/act_logic.h>

namespace game
{
    namespace internal
    {
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;
        using Matrix4 = glm::mat4;
        class Octant;
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
        inline constexpr float M_DEGTORAD_2 = M_PI / 360.0f;
        struct Plane
        {
            Vector3 n;
            float d;
            float Distance(Vector3 point) const
            {
                return glm::dot(point, n) + d;
            }
            void Define(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
            {

                Vector3 dist1 = v1 - v0;
                Vector3 dist2 = v2 - v0;
                Vector3 N = glm::normalize(glm::cross(dist1, dist2));
                n = N;
                d = -glm::dot(n, v0);
            }
        };
        class Frustum
        {
        public:
            Frustum() noexcept = default;

            Frustum(const Frustum &frustum) noexcept
            {
                *this = frustum;
            }

            Frustum &operator=(const Frustum &rhs) noexcept
            {
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

                near.z = nearZ;
                near.y = near.z * halfViewSize;
                near.x = near.y * aspectRatio;
                far.z = farZ;
                far.y = far.z * halfViewSize;
                far.x = far.y * aspectRatio;

                Define(near, far, transform);
            }

            void Define(const Vector3 &near, const Vector3 &far, const Matrix4 &transform = Matrix4(1.0f))
            {

                vertices_[0] = transform * Vector4(near, 1.0);
                vertices_[1] = transform * Vector4(near.x, -near.y, near.z, 1.0f);
                vertices_[2] = transform * Vector4(-near.x, -near.y, near.z, 1.0f);
                vertices_[3] = transform * Vector4(-near.x, near.y, near.z, 1.0f);
                vertices_[4] = transform * Vector4(far, 1.0);
                vertices_[5] = transform * Vector4(far.x, -far.y, far.z, 1.0f);
                vertices_[6] = transform * Vector4(-far.x, -far.y, far.z, 1.0f);
                vertices_[7] = transform * Vector4(-far.x, far.y, far.z, 1.0f);

                UpdatePlanes();
            }

            void Define(const Matrix4 &projection)
            {
                Matrix4 projInverse = glm::inverse(projection);
                vertices_[0] = projInverse * Vector4(1.0f, 1.0f, 0.0f, 1.0f);
                vertices_[1] = projInverse * Vector4(1.0f, -1.0f, 0.0f, 1.0f);
                vertices_[2] = projInverse * Vector4(-1.0f, -1.0f, 0.0f, 1.0f);
                vertices_[3] = projInverse * Vector4(-1.0f, 1.0f, 0.0f, 1.0f);
                vertices_[4] = projInverse * Vector4(1.0f, 1.0f, 1.0f, 1.0f);
                vertices_[5] = projInverse * Vector4(1.0f, -1.0f, 1.0f, 1.0f);
                vertices_[6] = projInverse * Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
                vertices_[7] = projInverse * Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
            }

            void DefineSplit(const Matrix4 &projection, float near, float far)
            {
                Matrix4 projInverse = glm::inverse(projection);

                Vector4 nearTemp = projection * Vector4(0.0f, 0.0f, near, 1.0f);
                Vector4 farTemp = projection * Vector4(0.0f, 0.0f, far, 1.0f);
                float nearZ = nearTemp.z / nearTemp.w;
                float farZ = farTemp.z / farTemp.w;

                vertices_[0] = projInverse * Vector4(1.0f, 1.0f, nearZ, 1.0f);
                vertices_[1] = projInverse * Vector4(1.0f, -1.0f, nearZ, 1.0f);
                vertices_[2] = projInverse * Vector4(-1.0f, -1.0f, nearZ, 1.0f);
                vertices_[3] = projInverse * Vector4(-1.0f, 1.0f, nearZ, 1.0f);
                vertices_[4] = projInverse * Vector4(1.0f, 1.0f, farZ, 1.0f);
                vertices_[5] = projInverse * Vector4(1.0f, -1.0f, farZ, 1.0f);
                vertices_[6] = projInverse * Vector4(-1.0f, -1.0f, farZ, 1.0f);
                vertices_[7] = projInverse * Vector4(-1.0f, 1.0f, farZ, 1.0f);

                UpdatePlanes();
            }

            Intersection IsInside(const Vector3 &point)
            {
                for (const auto &p : planes_)
                {
                    if (p.Distance(point) > 0)
                        return OUTSIDE;
                }

                return INSIDE;
            }

            Intersection IsInside(const Vector4 &sphere) const
            {
                bool allInside = true;
                for (const auto &plane : planes_)
                {
                    float dist = plane.Distance({sphere.x, sphere.y, sphere.z});
                    if (dist > sphere.w)
                        return OUTSIDE;
                    else if (dist > -sphere.w)
                        allInside = false;
                }

                return allInside ? INSIDE : INTERSECTS;
            }

            Intersection IsInside(const Vector3 &vmin, const Vector3 &vmax) const
            {
                Vector3 center = {(vmin.x + vmax.x) / 2, (vmin.y + vmax.y) / 2, (vmin.z + vmax.z) / 2};
                Vector3 edge = center - vmin;
                bool allInside = true;

                for (const auto &plane : planes_)
                {
                    float dist = plane.Distance(center);
                    Vector3 absNormal = {abs(plane.n.x), abs(plane.n.y), abs(plane.n.z)};
                    float absDist = glm::dot(absNormal, edge);

                    if (dist > absDist)
                        return OUTSIDE;
                    else if (dist > -absDist)
                        allInside = false;
                }

                return allInside ? INSIDE : INTERSECTS;
            }

            float Distance(const Vector3 &point) const
            {
                float distance = 0.0f;
                for (const auto &plane : planes_)
                    distance = plane.Distance(point) > distance ? plane.Distance(point) : distance;
                return distance;
            }

            void UpdatePlanes()
            {
                planes_[PLANE_NEAR].Define(vertices_[0], vertices_[1], vertices_[2]);
                planes_[PLANE_LEFT].Define(vertices_[6], vertices_[7], vertices_[3]);
                planes_[PLANE_RIGHT].Define(vertices_[4], vertices_[5], vertices_[1]);
                planes_[PLANE_UP].Define(vertices_[7], vertices_[4], vertices_[0]);
                planes_[PLANE_DOWN].Define(vertices_[1], vertices_[5], vertices_[6]);
                planes_[PLANE_FAR].Define(vertices_[7], vertices_[6], vertices_[5]);
            }
            Plane planes_[NUM_FRUSTUM_PLANES];

            Vector3 vertices_[NUM_FRUSTUM_VERTICES];
        };
        inline constexpr float M_INFINITY = std::numeric_limits<float>::infinity();
        class BoundingBox
        {
        public:
            BoundingBox() noexcept : min_(M_INFINITY, M_INFINITY, M_INFINITY),
                                     max_(-M_INFINITY, -M_INFINITY, -M_INFINITY)
            {
            }
            BoundingBox(const BoundingBox &box) noexcept : min_(box.min_),
                                                           max_(box.max_)
            {
            }
            BoundingBox(const Vector3 &min, const Vector3 &max) noexcept : min_(min),
                                                                           max_(max)
            {
            }

            BoundingBox(float min, float max) noexcept : min_(Vector3(min, min, min)),
                                                         max_(Vector3(max, max, max))
            {
            }

            explicit BoundingBox(const Frustum &frustum) : min_(M_INFINITY, M_INFINITY, M_INFINITY),
                                                           max_(-M_INFINITY, -M_INFINITY, -M_INFINITY)
            {
                Define(frustum);
            }
            BoundingBox &operator=(const BoundingBox &rhs) noexcept
            {
                min_ = rhs.min_;
                max_ = rhs.max_;
                return *this;
            }
            bool operator==(const BoundingBox &rhs) const { return (min_ == rhs.min_ && max_ == rhs.max_); }
            bool operator!=(const BoundingBox &rhs) const { return (min_ != rhs.min_ || max_ != rhs.max_); }
            void Define(const BoundingBox &box)
            {
                Define(box.min_, box.max_);
            }
            void Define(const Vector3 &min, const Vector3 &max)
            {
                min_ = min;
                max_ = max;
            }
            void Define(float min, float max)
            {
                min_ = Vector3(min, min, min);
                max_ = Vector3(max, max, max);
            }
            void Define(const Vector3 &point)
            {
                min_ = max_ = point;
            }
            void Merge(const Vector3 &point)
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
            void Merge(const BoundingBox &box)
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
            void Define(const Vector3 *vertices, unsigned count)
            {
                Clear();
                for (size_t i = 0; i < count; i++)
                {
                    Merge(vertices[i]);
                }
            }
            void Define(const Frustum &frustum)
            {
                Define(frustum.vertices_, 8);
            }
            void Merge(const Frustum &frustum)
            {
                for (size_t i = 0; i < 8; i++)
                {
                    Merge(frustum.vertices_[i]);
                }
            }
            void Clear()
            {
                min_ = Vector3(M_INFINITY, M_INFINITY, M_INFINITY);
                max_ = Vector3(-M_INFINITY, -M_INFINITY, -M_INFINITY);
            }
            bool Defined() const
            {
                return min_.x != M_INFINITY;
            }
            Vector3 Center() const { return (max_ + min_) * 0.5f; }
            Vector3 Size() const { return max_ - min_; }
            Vector3 HalfSize() const { return (max_ - min_) * 0.5f; }
            float DistanceToPoint(const Vector3 &point) const
            {
                const Vector3 offset = Center() - point;
                const Vector3 absOffset(abs(offset.x), abs(offset.y), abs(offset.z));
                return glm::max({0, 0, 0}, absOffset - HalfSize()).length();
            }
            Intersection IsInside(const Vector3 &point) const
            {
                if (point.x < min_.x || point.x > max_.x || point.y < min_.y || point.y > max_.y ||
                    point.z < min_.z || point.z > max_.z)
                    return OUTSIDE;
                else
                    return INSIDE;
            }
            Intersection IsInside(const BoundingBox &box) const
            {
                if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
                    box.max_.z < min_.z || box.min_.z > max_.z)
                    return OUTSIDE;
                else if (box.min_.x < min_.x || box.max_.x > max_.x || box.min_.y < min_.y || box.max_.y > max_.y ||
                         box.min_.z < min_.z || box.max_.z > max_.z)
                    return INTERSECTS;
                else
                    return INSIDE;
            }
            Intersection IsInsideFast(const BoundingBox &box) const
            {
                if (box.max_.x < min_.x || box.min_.x > max_.x || box.max_.y < min_.y || box.min_.y > max_.y ||
                    box.max_.z < min_.z || box.min_.z > max_.z)
                    return OUTSIDE;
                else
                    return INSIDE;
            }
            Vector3 min_;
            float dummyMin_{};
            Vector3 max_;
            float dummyMax_{};
        };
        class Drawable
        {
        public:
            //测试用的，主要是传入包围盒
            Drawable(BoundingBox box) : worldBoundingBox_(box)
            {
            }
            bool worldBoundingBoxDirty_ = false;
            virtual void OnWorldBoundingBoxUpdate() {}
            void SetOctant(Octant *octant) { octant_ = octant; }
            const BoundingBox &GetWorldBoundingBox()
            {
                if (worldBoundingBoxDirty_)
                {
                    OnWorldBoundingBoxUpdate();
                    worldBoundingBoxDirty_ = false;
                }

                return worldBoundingBox_;
            }
            Octant *octant_;

            BoundingBox worldBoundingBox_;
        };
        static const int NUM_OCTANTS = 8;
        static const unsigned ROOT_INDEX = 0xffffffff;
        class Octant
        {
        public:
            Octant(const BoundingBox &box, unsigned level, Octant *parent, Octant *root, unsigned index = ROOT_INDEX) : level_(level),
                                                                                                                        parent_(parent),
                                                                                                                        root_(root),
                                                                                                                        index_(index)
            {
                Initialize(box);
            }
            ~Octant()
            {
                drawables_.clear();
                numDrawables_ = 0;
                for (unsigned i = 0; i < NUM_OCTANTS; ++i)
                    DeleteChild(i);
            }

            Octant *GetOrCreateChild(unsigned index)
            {
                if (children_[index])
                    return children_[index];

                Vector3 newMin = worldBoundingBox_.min_;
                Vector3 newMax = worldBoundingBox_.max_;
                Vector3 oldCenter = worldBoundingBox_.Center();

                if (index & 1u)
                    newMin.x = oldCenter.x;
                else
                    newMax.x = oldCenter.x;

                if (index & 2u)
                    newMin.y = oldCenter.y;
                else
                    newMax.y = oldCenter.y;

                if (index & 4u)
                    newMin.z = oldCenter.z;
                else
                    newMax.z = oldCenter.z;

                children_[index] = new Octant(BoundingBox(newMin, newMax), level_ + 1, this, root_, index);
                return children_[index];
            }
            void DeleteChild(unsigned index)
            {
                assert(index < NUM_OCTANTS);
                delete children_[index];
                children_[index] = nullptr;
            }

            void InsertDrawable(Drawable *drawable)
            {

                const BoundingBox &box = drawable->GetWorldBoundingBox();
                bool insertHere;
                if (this == root_)
                    insertHere = cullingBox_.IsInside(box) != INSIDE || CheckDrawableFit(box);
                else
                    insertHere = CheckDrawableFit(box);

                if (insertHere)
                {
                    Octant *oldOctant = drawable->octant_;
                    if (oldOctant != this)
                    {
                        AddDrawable(drawable);
                        if (oldOctant)
                            oldOctant->RemoveDrawable(drawable, false);
                    }
                }
                else
                {
                    Vector3 boxCenter = box.Center();
                    unsigned x = boxCenter.x < center_.x ? 0 : 1;
                    unsigned y = boxCenter.y < center_.y ? 0 : 2;
                    unsigned z = boxCenter.z < center_.z ? 0 : 4;

                    GetOrCreateChild(x + y + z)->InsertDrawable(drawable);
                }
            }
            bool CheckDrawableFit(const BoundingBox &box) const
            {
                Vector3 boxSize = box.Size();
                if (boxSize.x >= halfSize_.x || boxSize.y >= halfSize_.y ||
                    boxSize.z >= halfSize_.z)
                    return true;
                else
                {
                    if (box.min_.x <= worldBoundingBox_.min_.x - 0.5f * halfSize_.x ||
                        box.max_.x >= worldBoundingBox_.max_.x + 0.5f * halfSize_.x ||
                        box.min_.y <= worldBoundingBox_.min_.y - 0.5f * halfSize_.y ||
                        box.max_.y >= worldBoundingBox_.max_.y + 0.5f * halfSize_.y ||
                        box.min_.z <= worldBoundingBox_.min_.z - 0.5f * halfSize_.z ||
                        box.max_.z >= worldBoundingBox_.max_.z + 0.5f * halfSize_.z)
                        return true;
                }
                return false;
            }
            void AddDrawable(Drawable *drawable)
            {

                drawable->SetOctant(this);
                drawables_.push_back(drawable);
                IncDrawableCount();
            }
            void RemoveDrawable(Drawable *drawable, bool resetOctant = true)
            {
                int k = -1;
                for (int i = 0; i < drawables_.size(); i++)
                {
                    if (drawables_[i] == drawable)
                    {
                        k = i;
                        break;
                    }
                }
                if (k != -1)
                {
                    while (k < drawables_.size() - 1)
                    {
                        drawables_[k] = drawables_[k + 1];
                        k++;
                    }
                    drawables_.pop_back();
                    if (resetOctant)
                        drawable->SetOctant(nullptr);
                    DecDrawableCount();
                }
            }
            const BoundingBox &GetWorldBoundingBox() const { return worldBoundingBox_; }
            const BoundingBox &GetCullingBox() const { return cullingBox_; }
            unsigned GetLevel() const { return level_; }
            Octant *GetParent() const { return parent_; }
            Octant *GetRoot() const { return root_; }
            unsigned GetNumDrawables() const { return numDrawables_; }
            bool IsEmpty() { return numDrawables_ == 0; }
            void ResetRoot()
            {
                root_ = nullptr;
                for (size_t i = 0; i < drawables_.size(); ++i)
                    drawables_[i]->SetOctant(nullptr);

                for (auto &child : children_)
                {
                    if (child)
                        child->ResetRoot();
                }
            }
            void Initialize(const BoundingBox &box)
            {
                worldBoundingBox_ = box;
                center_ = box.Center();
                halfSize_ = 0.5f * box.Size();
                cullingBox_ = BoundingBox(worldBoundingBox_.min_ - halfSize_, worldBoundingBox_.max_ + halfSize_);
            }
            void IncDrawableCount()
            {
                ++numDrawables_;
                if (parent_)
                    parent_->IncDrawableCount();
            }
            void DecDrawableCount()
            {
                Octant *parent = parent_;
                --numDrawables_;
                if (!numDrawables_)
                {
                    if (parent)
                        parent->DeleteChild(index_);
                }
                if (parent)
                    parent->DecDrawableCount();
            }
            void QueryByFrustum(std::vector<Drawable *> &res, Frustum &fr)
            {

                auto cull = this->GetCullingBox();
                auto test = fr.IsInside(cull.min_, cull.max_);
                if (test == OUTSIDE)
                {
                    std::cout << this->drawables_.size() << std::endl;
                    return;
                }

                for (auto t : this->drawables_)
                {

                    auto &box = t->GetWorldBoundingBox();

                    test = fr.IsInside(box.min_, box.max_);
                    if (test != OUTSIDE)
                    {
                        res.push_back(t);
                    }
                }
                for (size_t i = 0; i < 8; i++)
                {
                    if (children_[i])
                    {
                        children_[i]->QueryByFrustum(res, fr);
                    }
                }
            }

            BoundingBox worldBoundingBox_;
            BoundingBox cullingBox_;
            std::vector<Drawable *> drawables_;
            Octant *children_[NUM_OCTANTS]{};
            Vector3 center_;
            Vector3 halfSize_;
            unsigned level_;
            unsigned numDrawables_{};
            Octant *parent_;
            Octant *root_;
            unsigned index_;
        };
    }

    enum class Space : char
    {
        Local = 1 << 0,
        World = 1 << 1
    };

    class Transform
    {
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

        void Translate(const glm::vec3 &vector, Space space = Space::World);
        void Translate(float x, float y, float z, Space space = Space::World);

        void Rotate(const glm::vec3 &axis, float angle, Space space);
        void Rotate(const glm::vec3 &eulers, Space space);
        void Rotate(float euler_x, float euler_y, float euler_z, Space space);

        void Scale(float scale);
        void Scale(const glm::vec3 &scale);
        void Scale(float scale_x, float scale_y, float scale_z);

        void SetPosition(const glm::vec3 &position);
        void SetRotation(const glm::quat &rotation);
        void SetTransform(const glm::mat4 &transform);

        glm::vec3 Local2World(const glm::vec3 &v) const;
        glm::vec3 World2Local(const glm::vec3 &v) const;

        glm::mat4 GetLocalTransform() const;
        glm::mat4 GetLocalTransform(const glm::vec3 &forward, const glm::vec3 &up) const;
    };

    class BoxDraw : public mc::asset::ActLogic
    {
    public:
        struct Camera
        {
            GLFWwindow *window;
            glm::mat4 projection;
            Transform t;
            Camera();
            void Update(float t);
            void ResetView();
            glm::vec2 ConvertScreenToWorld(const glm::vec2 &screenPoint);
            glm::vec2 ConvertWorldToScreen(const glm::vec2 &worldPoint);
            void BuildProjectionMatrix(float *m, float zBias);
            glm::vec2 m_center;
            float m_zoom;
            int m_width;
            int m_height;
        };
        static Camera g_camera;
        struct GLRenderPoints
        {
            void create()
            {
#pragma region 创建着色器程序
                const char *V =
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

                const char *F =
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
                if (!success)
                {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "片段着色器编译成功" << std::endl;
                }

                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);

                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);

#pragma endregion

                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0); //位置属性
                glEnableVertexAttribArray(1); //颜色属性
                glEnableVertexAttribArray(2); //大小属性
                glGenBuffers(3, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[2]);
                glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(size), size, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;
            }
            void Vertex(const glm::vec2 &v, const glm::vec4 &c, float s)
            { //在缓冲区中送入一个顶点
                if (m_count == 1024)
                { //缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;
                size[m_count] = s;
                m_count++;
            }
            void fflush()
            { //实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码

                glUseProgram(shader);

                float p[16] = {0.0};
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
            unsigned int m_count; //点的数目
            unsigned int vaoId;   //
            unsigned int bufferId[3];
            unsigned int shader; //着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec2 vertices[maxCount]; //位置
            glm::vec4 color[maxCount];    //颜色
            float size[maxCount];         //大小
            int projection;
        };
        struct GLRenderLines
        {
            void create()
            {
#pragma region 创建着色器程序
                const char *V =
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

                const char *F =
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
                if (!success)
                {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "片段着色器编译成功" << std::endl;
                }
                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);
                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);
#pragma endregion
                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0); //位置属性
                glEnableVertexAttribArray(1); //颜色属性
                glGenBuffers(2, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
                m_count = 0;
            }
            void Vertex(const glm::vec3 &v, const glm::vec4 &c)
            { //在缓冲区中送入一个顶点
                if (m_count == 1024)
                { //缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;
                m_count++;
            }
            void fflush()
            { //实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码
                glUseProgram(shader);
                float p[16] = {0.0};
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
            unsigned int m_count; //点的数目
            unsigned int vaoId;   //
            unsigned int bufferId[2];
            unsigned int shader; //着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec3 vertices[maxCount]; //位置
            glm::vec4 color[maxCount];    //颜色
            int projection;
        };
        struct GLRenderTriangles
        {
            void create()
            {
#pragma region 创建着色器程序
                const char *V =
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

                const char *F =
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
                if (!success)
                {
                    glad_glGetShaderInfoLog(vP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "顶点着色器编译成功" << std::endl;
                }
                glCompileShader(fP);
                glGetShaderiv(fP, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glad_glGetShaderInfoLog(fP, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "片段着色器编译成功" << std::endl;
                }

                shader = glCreateProgram();
                glAttachShader(shader, vP);
                glAttachShader(shader, fP);

                glLinkProgram(shader);
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glad_glGetProgramInfoLog(shader, 512, NULL, infolog);
                    std::cout << infolog << std::endl;
                }
                else
                {
                    std::cout << "着色器链接成功" << std::endl;
                }
                glDeleteShader(vP);
                glDeleteShader(fP);

#pragma endregion

                projection = glGetUniformLocation(shader, "projectionMatrix");
                glGenVertexArrays(1, &vaoId);
                glBindVertexArray(vaoId);
                glEnableVertexAttribArray(0); //位置属性
                glEnableVertexAttribArray(1); //颜色属性

                glGenBuffers(2, bufferId);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
                glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                m_count = 0;
            }
            void Vertex(const glm::vec3 &v, const glm::vec4 &c)
            { //在缓冲区中送入一个顶点
                if (m_count == maxCount)
                { //缓冲区的数据满了
                    fflush();
                }
                vertices[m_count] = v;
                color[m_count] = c;

                m_count++;
            }
            void fflush()
            { //实际的绘制操作
                if (m_count == 0)
                    return;
                //后面可以加设置投影矩阵的代码

                glUseProgram(shader);
                float p[16] = {0.0};
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
            unsigned int m_count; //点的数目
            unsigned int vaoId;   //
            unsigned int bufferId[2];
            unsigned int shader; //着色器程序
            static const int maxCount = 1024 * 32;
            glm::vec3 vertices[maxCount]; //位置
            glm::vec4 color[maxCount];    //颜色}drawtriangles;
            int projection;
        };
        class DebugDraw
        {
        public:
            DebugDraw();
            ~DebugDraw();

            void Create();
            void Destroy();
            void DrawBoundBox(const internal::BoundingBox &box, const glm::vec4 &color, bool flag = true);
            void DrawBound(const glm::vec3 &center, const glm::vec3 &extent, const glm::vec4 &color, bool flag = true);
            void DrawPolygon(const glm::vec3 *vertices, int vertexCount, const glm::vec4 &color);

            void DrawSolidPolygon(const glm::vec3 *vertices, int vertexCount, const glm::vec4 &color);

            void DrawCircle(const glm::vec3 &center, float radius, const glm::vec3 &axis, const glm::vec4 &color, bool flag = true);

            void DrawSegment(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec4 &color);

            void DrawFrustum(const internal::Frustum &frustum, const glm::vec4 &color, bool flag = true) const;

            void DrawPoint(const glm::vec2 &p, float size, const glm::vec4 &color);
            void DrawOctant(const internal::Octant &octant, const glm::vec4 &color);

            void Flush();

        private:
            GLRenderPoints *m_points;
            GLRenderLines *m_lines;
            GLRenderTriangles *m_triangles;
        };
        static DebugDraw maindraw;

    private:
        static std::shared_ptr<mc::asset::ActLogic> createFunc(mc::low::GameObject *gb, const std::string &bin_data);

    public:
        ~BoxDraw() override;

    public:
        static void Register(mc::asset::ActLogicFactory &acf);

    public:
        void Update(double delta_time) override;
        void BeforeRenderUpdate(double delta_time) override;
        void AfterRenderUpdate(double delta_time) override;
    };
}
#endif // !BOX_DRAW_H
