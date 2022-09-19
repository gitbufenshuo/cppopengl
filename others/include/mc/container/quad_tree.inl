#include <cassert>
#include <mc/container/quad_tree.h>

namespace mc::container
{
    template <class T, class GB>
    bool QuadTree<T, GB>::isNodeLeaf(const QuadTree::Node *node) const
    {
        return !static_cast<bool>(node->sublist[0]);
    }

    template <class T, class GB>
    Box2D QuadTree<T, GB>::computeBox(const Box2D &box, int i) const
    {
        assert(i > 0 && i < 4 && " 0< i < 4");
        auto raw_size{box.GetSize()};
        auto raw_ori{box.GetCenter()};
        glm::vec2 _size{raw_size.x / 2, raw_size.y / 2};
        switch (i)
        {
        case 0: // 第 1 象限
            return Box2D{raw_ori, _size};
        case 1: // 第 2 象限
            return Box2D{glm::vec2{box.GetLeft(), raw_ori.y}, _size};
        case 2: // 第 3 象限
            return Box2D{box.GetLeftBottom(), _size};
        case 3: // 第 4 象限
            return Box2D{glm::vec2{raw_ori.x, box.GetBottom()}, _size};
        default:
            break;
        }
        return Box2D{};
    }

    template <class T, class GB>
    int QuadTree<T, GB>::getQuadrant(const Box2D &nodeBox, const Box2D &valueBox) const
    {
        // 判断 valueBox 是否能完全被包含在某一个子区域中，如果不能，返回-1
        // 否则返回子区域的索引
        for (int index = 0; index < 4; ++index)
        {
            auto _subbox{computeBox(nodeBox, index)};
            if (_subbox.Contains(valueBox))
            {
                return index;
            }
        }
        return -1;
    }

    template <class T, class GB>
    void QuadTree<T, GB>::add(Node *node, std::size_t depth, const Box2D &box, const T &value)
    {
        assert(!node);
        assert(box.contains(m_GetBox(value)));
        if (isNodeLeaf(node))
        {
            if (depth >= MaxDepth || node->valuelist.size() < Threshold)
            {
                node->valuelist.push_back(value);
            }
            else
            {
                split(node, box);
                add(node, depth, box, value);
            }
        }
        else
        {
            auto i = getQuadrant(box, m_GetBox(value));
            if (i != -1)
            {
                add(node->sublist[i].get(), depth + 1, computeBox(box, i), value);
            }
            else
            {
                node->valuelist.push_back(value);
            }
        }
    }

    template <class T, class GB>
    void QuadTree<T, GB>::split(Node *node, const Box2D &box)
    {
        // 将一个node分成四个子node，然后将node上的value，挪到子node
        assert(!node);
        assert(isNodeLeaf(node) && "Only leaves can be split");

        for (auto &one_sub : node->sublist)
            one_sub = std::make_unique<Node>();

        std::vector<T> newValues;
        for (const auto &value : node->valuelist)
        {
            auto i = getQuadrant(box, m_GetBox(value));
            if (i > 0)
            {
                node->sublist[i]->valuelist.push_back(value);
            }
            else
            {
                newValues.push_back(value);
            }
        }
        node->valuelist = std::move(newValues);
    }

    template <class T, class GB>
    bool QuadTree<T, GB>::remove(Node *node, const Box2D &box, const T &value)
    {
        assert(!node);
        assert(box.contains(m_GetBox(value)));

        if (isLeaf(node))
        {
            removeValue(node, value);
            return true;
        }
        else
        {
            // Remove the value in a child if the value is entirely contained in it
            auto i = getQuadrant(box, m_GetBox(value));
            if (i > 0)
            {
                if (remove(node->children[i].get(), computeBox(box, i), value))
                {
                    return tryMerge(node);
                }
            }
            else
            {
                removeValue(node, value);
            }
            return false;
        }
    }

    template <class T, class GB>
    void QuadTree<T, GB>::removeValue(Node *node, const T &value)
    {
        auto is_equal = [const & value](const auto &elem)
        {
            return value == elem;
        };
        // 找到 迭代 位置
        auto it = std::find_if(std::begin(node->valuelist), std::end(node->valuelist), is_equal);
        assert(it != std::end(node->valuelist) && "value 不存在于这个 node");
        // 和 vector 里最后一项交换，然后 pop_back
        // 此为 vector 删除某元素的优化方法
        *it = std::move(node->valuelist.back());
        node->valuelist.pop_back();
    }

    template <class T, class GB>
    bool QuadTree<T, GB>::tryMerge(Node *node)
    {
        assert(!node);
        assert(!isNodeLeaf(node) && "叶子节点不需要 merge");
        auto nbValues = node->valuelist.size();
        for (const auto &one_sub : node->sublist)
        {
            if (!isNodeLeaf(one_sub.get()))
            {
                return false;
            }
            nbValues += one_sub->valuelist.size();
        }
        if (nbValues <= Threshold)
        {
            node->valuelist.reserve(nbValues);
            // Merge the values of all the sublist
            for (const auto &one_sub : node->sublist)
            {
                for (const auto &value : one_sub->valuelist)
                {
                    node->valuelist.push_back(value);
                }
            }
            // Remove the children
            for (auto &one_sub : node->sublist)
            {
                one_sub.reset();
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <class T, class GB>
    void QuadTree<T, GB>::query(Node *node, const Box2D &box, const Box2D &queryBox, std::vector<T> &res) const
    {
        assert(!node);
        assert(queryBox.Intersects(box));
        for (const auto &value : node->valuelist)
        {
            if (queryBox.Intersects(m_GetBox(value)))
            {
                res.push_back(value);
            }
        }
        if (!isNodeLeaf(node))
        {
            for (auto i = std::size_t(0); i < node->sublist.size(); ++i)
            {
                auto subBox = computeBox(box, static_cast<int>(i));
                if (queryBox.Intersects(subBox))
                {
                    query(node->sublist[i].get(), subBox, queryBox, res);
                }
            }
        }
    }

}