#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <utility>
#include<vector>

using namespace std;
#include"RBTree.h"
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
class Solution0 {
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if (p == nullptr || q == nullptr)
        {
            return p == q;
        }
        return p->val == q->val
            && isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        if (root == nullptr)
        {
            return false;
        }
        return isSameTree(root, subRoot)
            || isSubtree(root->left, subRoot)
            || isSubtree(root->right, subRoot);
    }
};

class Solution1 {
public:
    int arraySign(vector<int>& nums)
    {
        int res{ 1 };
        for (auto& x : nums)
        {
            if (x == 0)
            {
                return 0;
            }
            // 如果x是正数，res不变；如果x是负数，res的符号翻转
            res *= x > 0 ? 1 : -1;
        }
        // 如果res为1，则说明负数个数为偶数；如果res为-1，则说明负数个数为奇数
        return res;
    }
};
void test_insert() {
    RBTree<int, int> rbTree;

    // 插入一些键值对
    rbTree.Insert({ 1, 1 });
    rbTree.Insert({ 2, 2 });
    rbTree.Insert({ 3, 3 });
    rbTree.Insert({ 4, 4 });
    rbTree.Insert({ 5, 5 });


    std::cout << "Insertion test completed." << std::endl;
}
int main()
{
    test_insert();
	return 0;
}