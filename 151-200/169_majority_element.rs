use std::collections::HashMap;
use std::cmp::Eq;
use std::hash::Hash;

// TODO: improve
/// https://leetcode.com/problems/majority-element/
impl Solution {
    pub fn majority_element<T>(list: Vec<T>) -> T
            where T: Copy + Hash + Eq {
        let bound = Solution::get_majority_bound(&list);
        let mut occurrences: HashMap<T, usize> = HashMap::new();
        for &e in list.iter() {
            let count = occurrences.entry(e).or_insert(0);
            *count += 1;
            if *count >= bound {
                return e;
            }
        }
        panic!("The specified list should contain a majority element.");
    }
    
    fn get_majority_bound<T>(list: &Vec<T>) -> usize
            where T: Copy + Hash + Eq {
        let len = list.len();
        if len % 2 == 0 {
            len / 2
        } else {
            len / 2 + 1
        }
    }
}
