#include <unordered_map>
#include <set>
#include <cstdlib>

class Solution {
public:
    bool containsNearbyAlmostDuplicate(const vector<int>& nums,
                                       const int indexDiff,
                                       const int valueDiff) {
        const int n = nums.size();
        if (indexDiff < 1 || n < 2) return false;

        // Negative valueDiffs are not supported anyway.
        if (valueDiff < 1) {
            std::unordered_map<int, int> m;
            m.reserve(n);
            for (int i = 0; i < n; i++) {
                const int num = nums[i];
                auto it = m.find(num);
                if (it != m.end()) {
                    const int j = it->second;
                    if (abs(i - j) <= indexDiff) return true;
                }
                m[num] = i;
            }
            return false;
        }

        if (indexDiff < 5) {
            for (int i = 0; i < n; i++) {
                const int a = nums[i];
                const int lb = max(0, i-indexDiff);
                const int ub = min(i+indexDiff, n-1);
                for (int j = lb; j <= ub; j++) {
                    const int b = nums[j];
                    if (i != j && abs(a - b) <= valueDiff) return true;
                }
            }
            return false;
        }

        std::set<int> w;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (i > indexDiff) w.erase(nums[i-indexDiff-1]);
            auto it = w.lower_bound(num-valueDiff);
            if (it != w.end() && abs(*it-num) <= valueDiff) return true;
            w.insert(num);
        }
        return false;
    }
};
