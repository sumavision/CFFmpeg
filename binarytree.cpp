#include "binarytree.h"
#include <iostream>
#include <stack>
using namespace std;

BinTNode *createBinTree()
{
    int data = 0;
    BinTNode *node = nullptr;

    cin>>data;

    if(data == -1)
    {
        return nullptr;
    }

    node = new BinTNode;
    node->data = data;
    node->left = createBinTree();
    node->right= createBinTree();

    return node;
}

/**
 * 销毁二叉树
 */
void destroyBinTree(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }
    destroyBinTree(node->left);
    destroyBinTree(node->right);
    delete node;
}

/**
 * 二叉树遍历---递归前序遍历
 * 基本思想：先访问根结点，再先序遍历左子树，最后再先序遍历右子树即根—左—右。
 */
void preorderTraverse(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }
    cout<<"current node = "<<node->data<<endl;
    preorderTraverse(node->left);
    preorderTraverse(node->right);
}
/**
 * 二叉树遍历---非递归前序遍历
 * 对于任一结点p:
 * a. 访问结点p，并将结点p入栈;
 * b. 判断结点p的左孩子是否为空，若为空，则取栈顶结点并进行出栈操作，并将栈顶结点的右孩子置为当前的结点p，循环置a；若不为空，则将p的左孩子置为当前结点p；
 * c. 直到p为空，并且栈为空，则遍历结束。
 */
void nonPreorderTraverse(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }

    stack<BinTNode*> sta;
    sta.push(node);

    while(!sta.empty())
    {
        BinTNode* curr = sta.top();
        sta.pop();

        cout<<"current node = "<<curr->data<<endl;

        if(curr->right != nullptr)
            sta.push(curr->right);
        if(curr->left != nullptr)
            sta.push(curr->left);
    }

}
/**
 * 二叉树遍历---递归中序遍历
 * 基本思想：先中序遍历左子树，然后再访问根结点，最后再中序遍历右子树即左—根—右。
 */
void inorderTraverse(BinTNode*node)
{
    if(nullptr == node)
    {
        return;
    }
    inorderTraverse(node->left);
    cout<<"current node = "<<node->data<<endl;
    inorderTraverse(node->right);
}
/**
 * 二叉树遍历---非递归中序遍历
 * 根据中序遍历的顺序，对于任一结点，优先访问其左孩子，而左孩子结点又可以看做一个根结点，
 * 然后继续访问其左孩子结点，直到遇到左孩子结点为空的结点才停止访问，然后按相同的规则访问其右子树。
 * 其处理过程如下：
 * 对于任一结点：
 * a. 若其左孩子不为空，则将p入栈，并将p的左孩子设置为当前的p，然后对当前结点再进行相同的操作；
 * b. 若其左孩子为空，则取栈顶元素并进行出栈操作，访问该栈顶结点，然后将当前的p置为栈顶结点的右孩子；
 * c. 直到p为空并且栈为空，则遍历结束。
 */
void nonInorderTraverse(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }

    stack<BinTNode*> sta;

    while(!sta.empty() || node != nullptr)
    {
        if(node == nullptr)
        {
            BinTNode *curr = sta.top();
            sta.pop();

            cout<<"current node = "<<curr->data<<endl;
            node = curr->right;
        }
        else
        {
            sta.push(node);
            node = node->left;
        }
    }
}
/**
 * 二叉树遍历---递归后序遍历
 * 基本思想：先后序遍历左子树，然后再后序遍历右子树，最后再访问根结点即左—右—根
 */
void postorderTraverse(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }
    inorderTraverse(node->left);
    inorderTraverse(node->right);
    cout<<"current node = "<<node->data<<endl;
}
/**
 * 二叉树遍历---非递归后序遍历
 * 后序遍历的非递归实现是三种遍历方式中最难的一种。
 * 因为在后序遍历中，要保证左孩子和右孩子都已被访问，并且左孩子在右孩子之前访问才能访问根结点，这就为流程控制带来了难题。
 * 下面介绍一种思路:
 * 要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点p，先将其入栈。
 * 若p不存在左孩子和右孩子，则可以直接访问它，或者p存在左孩子或右孩子，但是其左孩子和右孩子都已经被访问过了，则同样可以直接访问该结点。
 * 若非上述两种情况，则将p的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子之前别访问，左孩子和右孩子都在根结点前面被访问。
 */
void nonPostorderTraverse(BinTNode* node)
{
    if(nullptr == node)
    {
        return;
    }

    BinTNode *pre = nullptr;

    stack<BinTNode*> sta;
    sta.push(node);

    while(!sta.empty())
    {
        BinTNode *curr = sta.top();
        if((node->left == nullptr && node->right == nullptr)
                || (pre != nullptr && (curr->left == pre || curr->right == pre)))
        {
            sta.pop();
            cout<<"current node = "<<curr->data<<endl;
            pre = curr;
        }
        else
        {
            if(curr->left)
                sta.push(curr->left);

            if(curr->right)
                sta.push(curr->right);
        }
    }
}

