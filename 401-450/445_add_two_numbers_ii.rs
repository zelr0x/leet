// Problem: https://leetcode.com/problems/add-two-numbers-ii/description/
// Solution: https://leetcode.com/problems/add-two-numbers-ii/solutions/7534446/rust-100-time-and-memory-practically-o1-nszmo/

// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
// 
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }
impl Solution {
    pub fn add_two_numbers(
        l1: Option<Box<ListNode>>,
        l2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        if l1.is_none() || l2.is_none() {
            return l1.or(l2);
        }
        let mut s1: Vec<i32> = to_vec(l1);
        let mut s2: Vec<i32> = to_vec(l2);
        let mut carry: i32 = 0;
        let mut res: Option<Box<ListNode>> = None;
        let mut n = s1.len();
        let s2_len = s2.len();
        if n != s2_len {
            if s2_len > n {
                prepend_zeroes(&mut s1, s2_len-n);
                n = s2_len;
            } else {
                prepend_zeroes(&mut s2, n-s2_len);
            }
        }
        assert!(s1.len() == n && s2.len() == n, "Lengths must match");
        for _ in 0..n {
            let d1 = s1.pop().unwrap();
            let d2 = s2.pop().unwrap();
            let sum = d1+d2+carry;
            carry = sum / 10;
            let mut node = ListNode::new(sum % 10);
            node.next = res;
            res = Some(Box::new(node));
        }
        if carry > 0 {
            let mut node = ListNode::new(carry);
            node.next = res;
            res = Some(Box::new(node));
        }
        return res;
    }
}

fn to_vec(list: Option<Box<ListNode>>) -> Vec<i32> {
    let mut list = list;
    let mut res = Vec::<i32>::new();
    while let Some(node) = list {
        res.push(node.val);
        list = node.next;
    }
    return res;
}

fn prepend_zeroes(v: &mut Vec<i32>, n: usize) {
    let old_len = v.len();
    let new_len = old_len + n;
    if new_len <= old_len {
        return;
    }
    v.resize(new_len, 0);
    unsafe {
        let ptr = v.as_mut_ptr();
        std::ptr::copy(ptr, ptr.add(n), old_len);
        std::ptr::write_bytes(ptr, 0, n);
    }
}
