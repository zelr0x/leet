// Problem: https://leetcode.com/problems/add-two-numbers/
// Solution: https://leetcode.com/problems/add-two-numbers/solutions/7534643/branchless-rust-100-time-practically-o1-4i6l4/

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
        let mut n = s1.len();
        let s2_len = s2.len();
        if n != s2_len {
            if s2_len > n {
                append_zeroes(&mut s1, s2_len-n);
                n = s2_len;
            } else {
                append_zeroes(&mut s2, n-s2_len);
            }
        }
        assert!(s1.len() == n && s2.len() == n, "Lengths must match");
        let mut dummy = Box::new(ListNode::new(0));
        let mut tail = &mut dummy;
        for i in 0..n {
            let sum = s1[i] + s2[i] + carry;
            carry = sum / 10;
            tail.next = Some(Box::new(ListNode::new(sum % 10)));
            tail = tail.next.as_mut().unwrap();
        }
        if carry > 0 {
            tail.next = Some(Box::new(ListNode::new(carry)));
        }
        dummy.next
    }
}

fn to_vec(list: Option<Box<ListNode>>) -> Vec<i32> {
    let mut list = list;
    let mut res = Vec::<i32>::new();
    while let Some(node) = list {
        res.push(node.val);
        list = node.next;
    }
    res
}

fn append_zeroes(v: &mut Vec<i32>, n: usize) {
    let old_len = v.len();
    let new_len = old_len + n;
    if new_len <= old_len {
        return;
    }
    v.resize(new_len, 0);
}
