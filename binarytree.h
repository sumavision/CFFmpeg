#ifndef BINARYTREE_H
#define BINARYTREE_H


/**
 * 二叉树节点，包含左右子节点以及节点数据
 */
struct BinTNode
{
    BinTNode *left;
    BinTNode *right;
    int data;
};

/**
 * 创建二叉树
 */
BinTNode *createBinTree();

/**
 * 销毁二叉树
 */
void destroyBinTree(BinTNode* node);

/**
 * 二叉树遍历---递归前序遍历
 */
void preorderTraverse(BinTNode* node);
/**
 * 二叉树遍历---非递归前序遍历
 */
void nonPreorderTraverse(BinTNode* node);

/**
 * 二叉树遍历---递归中序遍历
 */
void inorderTraverse(BinTNode* node);
/**
 * 二叉树遍历---非递归中序遍历
 */
void nonInorderTraverse(BinTNode* node);

/**
 * 二叉树遍历---递归后序遍历
 */
void postorderTraverse(BinTNode* node);
/**
 * 二叉树遍历---非递归后序遍历
 */
void nonPostorderTraverse(BinTNode* node);

#endif // BINARYTREE_H
