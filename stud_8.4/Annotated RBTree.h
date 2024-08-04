#pragma once

enum Colour {
    RED,       // �ڵ���ɫ����ɫ
    BLACK      // �ڵ���ɫ����ɫ
};

// ���������Ľڵ�ṹ��ʹ��ģ����֧�ַ���
template<class K, class V>
struct RBTreeNode {
    pair<K, V> _kv;        // �����ֵ��
    RBTreeNode<K, V>* _left; // ���ӽڵ�ָ��
    RBTreeNode<K, V>* _right; // ���ӽڵ�ָ��
    RBTreeNode<K, V>* _parent; // ���ڵ�ָ��
    Colour _col;            // �ڵ���ɫ

    // ���캯������ʼ���ڵ�
    RBTreeNode(const pair<K, V>& kv)
        : _kv(kv)          // ��ʼ����ֵ��
        , _left(nullptr)   // ��ʼ�����ӽڵ�ָ��Ϊnullptr
        , _right(nullptr)  // ��ʼ�����ӽڵ�ָ��Ϊnullptr
        , _parent(nullptr) // ��ʼ�����ڵ�ָ��Ϊnullptr
        , _col(RED)        // ��ʼ����ɫΪ��ɫ
    {}
};

// ���������࣬ʹ��ģ����֧�ַ���
template<class K, class V>
class RBTree {
    // ʹ�ñ����򻯽ڵ����͵���д
    typedef RBTreeNode<K, V> Node;

public:
    // �����ֵ�ԵĽӿ�
    bool Insert(const pair<K, V>& kv) {
        // �����Ϊ�գ��򴴽����ڵ�
        if (_root == nullptr) {
            _root = new Node(kv);
            _root->_col = BLACK; // ���ø��ڵ���ɫΪ��ɫ
            return true;
        }

        // ���Ҳ���λ�õĸ��ڵ�
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur) {
            if (cur->_kv.first < kv.first) {
                parent = cur;
                cur = cur->_right; // ������������
            }
            else if (cur->_kv.first > kv.first) {
                parent = cur;
                cur = cur->_left; // ������������
            }
            else {
                return false; // �����ֵ�Ѵ��ڣ������ʧ��
            }
        }

        // �����½ڵ�
        cur = new Node(kv);
        cur->_col = RED; // �½ڵ���ɫĬ��Ϊ��ɫ
        if (parent->_kv.first < kv.first) {
            parent->_right = cur; // ���뵽���ڵ��������
            cur->_parent = parent; // �����½ڵ�ĸ��ڵ�
        }
        else {
            parent->_left = cur; // ���뵽���ڵ��������
            cur->_parent = parent; // �����½ڵ�ĸ��ڵ�
        }

        // ��ʼƽ�����
        while (parent && parent->_col == RED) {
            Node* grandfater = parent->_parent;
            if (parent == grandfater->_left) {
                Node* uncle = grandfater->_right;
                // ���������Ϊ��ɫ�����
                if (uncle && uncle->_col == RED) {
                    parent->_col = uncle->_col = BLACK;
                    grandfater->_col = RED;

                    cur = grandfater;
                    parent = cur->_parent;
                }
                else {
                    if (cur == parent->_left) {
                        // ������������������������
                        RotateR(grandfater);
                        parent->_col = BLACK;
                        grandfater->_col = RED;
                    }
                    else {
                        // ����������������������������
                        RotateL(parent);
                        RotateR(grandfater);
                        cur->_col = BLACK;
                        grandfater->_col = RED;
                    }

                    break;
                }
            }
            else {
                // ���������������
                // ע�⣺�ⲿ�ִ���δ��ɣ���Ҫ���ݺ�����Ĺ���ȫ
            }
        }

        // ���ø��ڵ���ɫΪ��ɫ�����ֺ��������
        _root->_col = BLACK;

        return true;
    }

    // ��������������ƽ�����
    void RotateL(Node* parent) {
        Node* subR = parent->_right; // ��ȡ���ڵ�����ӽڵ�
        Node* subRL = subR->_left; // ��ȡ���ӽڵ�����ӽڵ�

        parent->_right = subRL; // �����ڵ�����ӽڵ���Ϊ���ӽڵ�����ӽڵ�
        if (subRL) {
            subRL->_parent = parent; // �������ӽڵ�����ӽڵ�ĸ��ڵ�
        }

        Node* ppNode = parent->_parent; // ��ȡ���ڵ�ĸ��ڵ�
        subR->_left = parent; // �����ӽڵ�����ӽڵ���Ϊ���ڵ�
        parent->_parent = subR; // ���¸��ڵ�ĸ��ڵ�

        // ���¸��ڵ�򸸽ڵ���ӽڵ�
        if (ppNode == nullptr) {
            _root = subR; // ������ڵ�ĸ��ڵ�Ϊ�գ�����¸��ڵ�
            _root->_parent = nullptr; // ���¸��ڵ�ĸ��ڵ�Ϊ��
        }
        else {
            if (ppNode->_left == parent) {
                ppNode->_left = subR; // ������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
            }
            else {
                ppNode->_right = subR; // ������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
            }

            subR->_parent = ppNode; // �������ӽڵ�ĸ��ڵ�
        }

        // ���½ڵ��ƽ������
        parent->_bf = subR->_bf = 0;
    }

    // ��������������ƽ�����
    void RotateR(Node* parent) {
        Node* subL = parent->_left; // ��ȡ���ڵ�����ӽڵ�
        Node* subLR = subL->_right; // ��ȡ���ӽڵ�����ӽڵ�

        parent->_left = subLR; // �����ڵ�����ӽڵ���Ϊ���ӽڵ�����ӽڵ�
        if (subLR) {
            subLR->_parent = parent; // �������ӽڵ�����ӽڵ�ĸ��ڵ�
        }

        Node* ppNode = parent->_parent; // ��ȡ���ڵ�ĸ��ڵ�
        subL->_right = parent; // �����ӽڵ�����ӽڵ���Ϊ���ڵ�
        parent->_parent = subL; // ���¸��ڵ�ĸ��ڵ�

        // ���¸��ڵ�򸸽ڵ���ӽڵ�
        if (ppNode == nullptr) {
            _root = subL; // ������ڵ�ĸ��ڵ�Ϊ�գ�����¸��ڵ�
            _root->_parent = nullptr; // ���¸��ڵ�ĸ��ڵ�Ϊ��
        }
        else {
            if (ppNode->_left == parent) {
                ppNode->_left = subL; // ������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
            }
            else {
                ppNode->_right = subL; // ������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
            }

            subL->_parent = ppNode; // �������ӽڵ�ĸ��ڵ�
        }

        // ���½ڵ��ƽ������
        subL->_bf = parent->_bf = 0;
    }

private:
    Node* _root = nullptr; // ���ڵ�ָ��
};
