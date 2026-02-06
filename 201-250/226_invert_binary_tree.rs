// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;

impl Solution {
    pub fn invert_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        if let Some(root) = root.as_ref().cloned() {
            let mut stack = Vec::new();
            stack.push(root);
            while let Some(node) = stack.pop() {
                let TreeNode { left, right , .. } = &mut *node.borrow_mut();
                std::mem::swap(left, right);
                if let Some(x) = left.clone() {
                    stack.push(x);
                }
                if let Some(x) = right.clone() {
                    stack.push(x);
                }
            }
        }
        root
    }
}
