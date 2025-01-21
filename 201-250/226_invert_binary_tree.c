#include <stddef.h>

static inline void swap(struct TreeNode **a, struct TreeNode **b) {
    struct TreeNode *t = *a;
    *a = *b;
    *b = t;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    if (root != NULL) {
        swap(&root->left, &root->right);
        invertTree(root->left);
        invertTree(root->right);
    }
    return root;
}
