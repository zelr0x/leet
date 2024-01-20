class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        indices = {}
        for i, num in enumerate(nums):
            if num in indices:
                indices[num].append(i)
            else:
                indices[num] = [i]
        for first, first_indices in indices.items():
            second = target - first
            if second == first:
                if len(first_indices) > 1:
                    return first_indices[:2]
                else:
                    continue
            if second in indices:
                second_indices = indices[second]
                return [first_indices[0], second_indices[0]]
