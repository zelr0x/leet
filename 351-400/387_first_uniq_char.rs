use std::collections::HashMap;

// TODO: improve
/// https://leetcode.com/problems/first-unique-character-in-a-string/
impl Solution {
    pub fn first_uniq_char(s: String) -> i32 {
        let mut seen: HashMap<char, usize> = HashMap::new();
        for c in s.chars() {
            *seen.entry(c).or_insert(0) += 1;
        }
        for (i, e) in s.char_indices() {
            if let Some(1) = seen.get(&e) {
                return i as i32
            }
        }
        -1
    }
}
