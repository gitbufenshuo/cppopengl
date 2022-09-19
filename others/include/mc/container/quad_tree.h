#ifndef MC_CONTAINER_QUAD_TREE_H
#define MC_CONTAINER_QUAD_TREE_H
// https://github.com/pvigier/Quadtree/blob/master/include/Quadtree.h

#include <vector>
#include <memory>
#include <array>

#include <mc/container/box2d.h>

namespace mc::container
{
    template <class T>
    struct GetBox
    {
        Box2D operator(const T &input)
        {
            return input.GetBox2D();
        }
    };

    template <class T, class GB = GetBox<T>>
    class QuadTree
    {
    public:
        QuadTree(const Box2D &full,
                 const GetBox &getBox = GetBox{}) : m_full{box},
                                                    m_root(std::make_unique<Node>()),
                                                    m_GetBox(getBox)
        {
        }
        void Add(const T &value);
        void Remove(const T &value);
        std::vector<T> Query(const Box2D &box);

    private:
        struct Node
        {
            std::array<std::unique_ptr<Node>, 4> sublist;
            std::vector<T> valuelist;
        };

    private:
        Box2D m_full;                 // 整个世界的 box2d (最外层)
        std::unique_ptr<Node> m_root; // 四叉树的根节点
        GB m_GetBox;                  // 一个自定义的让T可以获得 Box2D 的 functor
        static constexpr auto Threshold = std::size_t(16);
        static constexpr auto MaxDepth = std::size_t(8);

    private:
        bool isNodeLeaf(const Node *node) const;         // 判断一个 Node 是否是叶子节点
        Box2D computeBox(const Box2D &box, int i) const; // 根据子节点索引，得到子节点的 box2d
        int getQuadrant(const Box2D &nodeBox, const Box2D &valueBox) const;
        void add(Node *node, std::size_t depth, const Box2D &box, const T &value);
        void split(Node *node, const Box2D &box);
        bool remove(Node *node, const Box2D &box, const T &value);
        void removeValue(Node *node, const T &value);
        bool tryMerge(Node *node);
        void query(Node *node, const Box2D &box, const Box2D &queryBox, std::vector<T> &values) const;
    };
}
#include <mc/container/quad_tree.inl>
#endif