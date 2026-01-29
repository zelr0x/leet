// Exercise: https://leetcode.com/problems/valid-anagram/
// This solution has optimal performance: O(n) time, O(1) space
impl Solution {
    pub fn is_anagram(s: String, t: String) -> bool {
        if std::ptr::eq(&s, &t) {
            return true;
        }
        let n = s.len();
        if n != t.len() {
            return false;
        }
        let mut freq: [usize; 26] = [0; 26];
        s.bytes().for_each(|c| freq[ascii_lc_to_idx(c)] += 1);
        for c in t.bytes() {
            let i = ascii_lc_to_idx(c);
            if freq[i] < 1 {
                return false;
            }
            freq[i] -= 1;
        }
        return true;
    }
}

/// Must be called only with ASCII lowercase letters (b'a'..b'z').
#[inline(always)]
const fn ascii_lc_to_idx(c: u8) -> usize {
    return (c - b'a') as usize;
}
