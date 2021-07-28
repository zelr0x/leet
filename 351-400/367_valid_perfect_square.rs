use std::cmp::Ordering;

// TODO: optimize memory
/// https://leetcode.com/problems/valid-perfect-square/submissions/
impl Solution {
    /// 1 <= `num` <= 2^31 - 1
    pub fn is_perfect_square(num: i32) -> bool {
        let num = num as u64;
        if num == 1 {
            true
        } else {
            let mut l = 1;
            let mut r = num;
            while l <= r {
                let mid = (l + r) / 2;
                match (mid * mid).cmp(&num) {
                    Ordering::Less => l = mid + 1,
                    Ordering::Greater => r = mid - 1,
                    Ordering::Equal => return true,
                };
            }
            false
        }
    }
}
