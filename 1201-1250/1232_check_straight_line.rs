/// https://leetcode.com/problems/check-if-it-is-a-straight-line/
impl Solution {
    pub fn check_straight_line(coordinates: Vec<Vec<i32>>) -> bool {
        let len = coordinates.len();
        if (len < 2) {
            false
        } else if (len == 2) {
            true
        } else {
            let first = coordinates.get(0).unwrap();
            let second = coordinates.get(1).unwrap();
            let slope = Solution::slope_vec(first, second).unwrap();
            coordinates.windows(2).skip(1)
                .all(|e| {
                    let e_slope = Solution::slope(e);
                    e_slope.is_some() && e_slope.unwrap() == slope
                })
        }
    }        
    
    fn slope(point_pair: &[Vec<i32>]) -> Option<f64> {
        let a = point_pair.get(0)?;
        let b = point_pair.get(1)?;
        let x_a = a.get(0)?;
        let y_a = a.get(1)?;
        let x_b = b.get(0)?;
        let y_b = b.get(1)?;
        Some((y_b - y_a) as f64 / (x_b - x_a) as f64)
    }
    
    fn slope_vec(a: &Vec<i32>, b: &Vec<i32>) -> Option<f64> {
        let x_a = *a.get(0)?;
        let y_a = *a.get(1)?;
        let x_b = *b.get(0)?;
        let y_b = *b.get(1)?;
        Some((y_b - y_a) as f64 / (x_b - x_a) as f64)
    }
}
