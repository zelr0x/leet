#include <unordered_map>
#include <cstdlib>

class Solution {
public:
    bool containsNearbyDuplicate(const std::vector<int>& nums, const int k) {
        const int n = nums.size();
        if (k == 0 || n < 2) return false;
        std::unordered_map<int, int> m;
        m.reserve(n);
        for (int i = 0; i < n; i++) {
            const int num = nums[i];
            auto it = m.find(num);
            if (it != m.end()) {
                const int j = it->second;
                if (abs(i - j) <= k) return true;
            }
            m[num] = i;
        }
        return false;
    }
};
