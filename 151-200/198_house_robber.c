/**
 * Exercise: https://leetcode.com/problems/house-robber/
 *
 * Constraints:
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 400
 */

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

int rob(int* nums, int n) {
    int prev_max = 0;
    int curr_max = 0;
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        int t = curr_max;
        curr_max = MAX(prev_max + num, curr_max);
        prev_max = t;
    }
    return curr_max;
}
