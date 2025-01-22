#include <unordered_map>
#include <cstdlib>

class Solution {
public:
    bool containsNearbyDuplicate(const std::vector<int>& nums, const int k) {
        int n = nums.size();
        if (k == 0 || n < 2) return false;
        for (int i = 0; i < nums.size(); i++) {
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
private:
    std::unordered_map<int, int> m;
};
