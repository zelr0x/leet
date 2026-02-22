// Problem: https://leetcode.com/problems/binary-search/description/
// Solution: https://leetcode.com/problems/binary-search/solutions/7599507/go-beats-100-optimized-with-cutoff-by-ze-skys/

const cutoff = 16

func search(nums []int, target int) int {
	lo := 0
	hi := len(nums)
	for {
		n := hi - lo
		if n <= cutoff {
			for i, v := range nums[lo:hi] {
				if v == target {
					return lo + i
				}
			}
			return -1
		}
        mid := lo + n/2
		v := nums[mid]
		switch {
		case v < target:
			lo = mid + 1
		case v > target:
			hi = mid
		default:
			return mid
		}
	}
}

