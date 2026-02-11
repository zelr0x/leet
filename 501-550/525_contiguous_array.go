// Problem: https://leetcode.com/problems/contiguous-array/description/
func findMaxLength(nums []int) int {
    if len(nums) < 2 {
        return 0
    }
    sums := make(map[int]int)
    sums[0] = -1
    sum, maxLength := 0, 0
    for i, v := range nums {
        if v == 0 {
            sum--
        } else {
            sum++
        }
        if prevBalanceIdx, ok := sums[sum]; ok {
            maxLength = max(maxLength, i - prevBalanceIdx)
        } else {
            sums[sum] = i
        }
    }
    return maxLength
}
