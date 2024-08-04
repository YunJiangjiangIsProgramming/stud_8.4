#pragma once

enum Colour {
    RED,       // 节点颜色：红色
    BLACK      // 节点颜色：黑色
};

// 定义红黑树的节点结构，使用模板以支持泛型
template<class K, class V>
struct RBTreeNode {
    pair<K, V> _kv;        // 保存键值对
    RBTreeNode<K, V>* _left; // 左子节点指针
    RBTreeNode<K, V>* _right; // 右子节点指针
    RBTreeNode<K, V>* _parent; // 父节点指针
    Colour _col;            // 节点颜色

    // 构造函数：初始化节点
    RBTreeNode(const pair<K, V>& kv)
        : _kv(kv)          // 初始化键值对
        , _left(nullptr)   // 初始化左子节点指针为nullptr
        , _right(nullptr)  // 初始化右子节点指针为nullptr
        , _parent(nullptr) // 初始化父节点指针为nullptr
        , _col(RED)        // 初始化颜色为红色
    {}
};

// 定义红黑树类，使用模板以支持泛型
template<class K, class V>
class RBTree {
    // 使用别名简化节点类型的书写
    typedef RBTreeNode<K, V> Node;

public:
    // 插入键值对的接口
    bool Insert(const pair<K, V>& kv) {
        // 如果树为空，则创建根节点
        if (_root == nullptr) {
            _root = new Node(kv);
            _root->_col = BLACK; // 设置根节点颜色为黑色
            return true;
        }

        // 查找插入位置的父节点
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur) {
            if (cur->_kv.first < kv.first) {
                parent = cur;
                cur = cur->_right; // 向右子树搜索
            }
            else if (cur->_kv.first > kv.first) {
                parent = cur;
                cur = cur->_left; // 向左子树搜索
            }
            else {
                return false; // 如果键值已存在，则插入失败
            }
        }

        // 插入新节点
        cur = new Node(kv);
        cur->_col = RED; // 新节点颜色默认为红色
        if (parent->_kv.first < kv.first) {
            parent->_right = cur; // 插入到父节点的右子树
            cur->_parent = parent; // 设置新节点的父节点
        }
        else {
            parent->_left = cur; // 插入到父节点的左子树
            cur->_parent = parent; // 设置新节点的父节点
        }

        // 开始平衡调整
        while (parent && parent->_col == RED) {
            Node* grandfater = parent->_parent;
            if (parent == grandfater->_left) {
                Node* uncle = grandfater->_right;
                // 叔叔存在且为红色的情况
                if (uncle && uncle->_col == RED) {
                    parent->_col = uncle->_col = BLACK;
                    grandfater->_col = RED;

                    cur = grandfater;
                    parent = cur->_parent;
                }
                else {
                    if (cur == parent->_left) {
                        // 情况二：左左情况，进行右旋
                        RotateR(grandfater);
                        parent->_col = BLACK;
                        grandfater->_col = RED;
                    }
                    else {
                        // 情况三：左右情况，先左旋再右旋
                        RotateL(parent);
                        RotateR(grandfater);
                        cur->_col = BLACK;
                        grandfater->_col = RED;
                    }

                    break;
                }
            }
            else {
                // 处理右子树的情况
                // 注意：这部分代码未完成，需要根据红黑树的规则补全
            }
        }

        // 设置根节点颜色为黑色，保持红黑树性质
        _root->_col = BLACK;

        return true;
    }

    // 左旋操作，用于平衡调整
    void RotateL(Node* parent) {
        Node* subR = parent->_right; // 获取父节点的右子节点
        Node* subRL = subR->_left; // 获取右子节点的左子节点

        parent->_right = subRL; // 将父节点的右子节点设为右子节点的左子节点
        if (subRL) {
            subRL->_parent = parent; // 更新右子节点的左子节点的父节点
        }

        Node* ppNode = parent->_parent; // 获取父节点的父节点
        subR->_left = parent; // 将右子节点的左子节点设为父节点
        parent->_parent = subR; // 更新父节点的父节点

        // 更新根节点或父节点的子节点
        if (ppNode == nullptr) {
            _root = subR; // 如果父节点的父节点为空，则更新根节点
            _root->_parent = nullptr; // 更新根节点的父节点为空
        }
        else {
            if (ppNode->_left == parent) {
                ppNode->_left = subR; // 如果父节点是左子节点，则更新为右子节点
            }
            else {
                ppNode->_right = subR; // 如果父节点是右子节点，则更新为右子节点
            }

            subR->_parent = ppNode; // 更新右子节点的父节点
        }

        // 更新节点的平衡因子
        parent->_bf = subR->_bf = 0;
    }

    // 右旋操作，用于平衡调整
    void RotateR(Node* parent) {
        Node* subL = parent->_left; // 获取父节点的左子节点
        Node* subLR = subL->_right; // 获取左子节点的右子节点

        parent->_left = subLR; // 将父节点的左子节点设为左子节点的右子节点
        if (subLR) {
            subLR->_parent = parent; // 更新左子节点的右子节点的父节点
        }

        Node* ppNode = parent->_parent; // 获取父节点的父节点
        subL->_right = parent; // 将左子节点的右子节点设为父节点
        parent->_parent = subL; // 更新父节点的父节点

        // 更新根节点或父节点的子节点
        if (ppNode == nullptr) {
            _root = subL; // 如果父节点的父节点为空，则更新根节点
            _root->_parent = nullptr; // 更新根节点的父节点为空
        }
        else {
            if (ppNode->_left == parent) {
                ppNode->_left = subL; // 如果父节点是左子节点，则更新为左子节点
            }
            else {
                ppNode->_right = subL; // 如果父节点是右子节点，则更新为左子节点
            }

            subL->_parent = ppNode; // 更新左子节点的父节点
        }

        // 更新节点的平衡因子
        subL->_bf = parent->_bf = 0;
    }

private:
    Node* _root = nullptr; // 根节点指针
};
