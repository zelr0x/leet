// Exercise: https://leetcode.com/problems/invert-binary-tree/description/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func invertTree(root *TreeNode) *TreeNode {
    if root == nil {
        return nil;
    }
    stack := make([]*TreeNode, 0, 16)
    stack = append(stack, root)
    for len(stack) > 0 {
        lastIdx := len(stack)-1
        node := stack[lastIdx]
        stack = stack[:lastIdx]
        if node == nil {
            continue
        }
        node.Left, node.Right = node.Right, node.Left
        if node.Left != nil {
            stack = append(stack, node.Left)
        }
        if node.Right != nil {
            stack = append(stack, node.Right)
        }
    }
    return root
}
