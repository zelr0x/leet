// Problem: https://leetcode.com/problems/binary-search/description/
// Solution: https://leetcode.com/problems/binary-search/solutions/7600592/c-beats-100-optimized-with-cutoff-by-zel-3h8g/

#define CUTOFF 16

int search(int* nums, int numsSize, int target) {
    int lo = 0;
    int hi = numsSize;
    for (;;) {
        int n = hi - lo;
        if (n <= CUTOFF) {
            for (int i = 0; i < n; i++) {
                int k = lo + i;
                if (nums[k] == target) {
                    return k;
                }
            }
            return -1;
        }
        int mid = lo + n/2;
        int v = nums[mid];
        if (v < target) {
            lo = mid + 1;
        } else if (v > target) {
            hi = mid;
        } else {
            return mid;
        }
    }
}
