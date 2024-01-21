#include <inttypes.h>

/**
 * Exercise: https://leetcode.com/problems/two-sum/
 * Explanation: https://leetcode.com/problems/two-sum/solutions/4604021/c-0ms-beats-100-in-time-and-memory-static-allocation/
 *
 * Constaints:
 * 2 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 *
 * Only one valid answer exists.
 * The same number may appear in nums twice, but not more,
 * since that would violate only one valid answer constraint.
 * The indices in the result may be in any order.
 * 
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 2^14 is the smallest power of 2 that can fit 10^4
#define TAB_SZ 16384

typedef struct {
    int32_t key;
    int32_t value;
} Entry;

static Entry entries[TAB_SZ];
static Entry *tab[TAB_SZ];

static const size_t ENTRIES_BYTES = TAB_SZ * sizeof(Entry);
static const size_t TAB_BYTES = TAB_SZ * sizeof(Entry *);

static inline void clear() {
    memset(entries, 0, ENTRIES_BYTES);
    memset(tab, 0, TAB_BYTES);
}

static inline size_t hash(const int32_t key) {
    size_t k = (size_t)abs(key);
    k = k ^ (k << 30);
    k = k ^ (k >> 27);
    k = k ^ (k << 31);
    return k & (TAB_SZ - 1);
}

static inline size_t hash2(const int32_t key) {
    size_t k = (size_t)abs(key);
    k ^= (k >> 21);
    k ^= (k << 37);
    k ^= (k >> 13);
    return k & (TAB_SZ - 1);
}

static inline void insert(const int32_t key,
                          const int32_t value) {
    size_t h = hash(key);
    size_t h2 = 1;
    for (size_t i = 0; i < TAB_SZ; ++i) {
        size_t idx = (h + i * h2) % TAB_SZ;
        Entry *entry = tab[idx];
        if (!entry) {
            entry = &entries[idx];
            entry->key = key;
            entry->value = value;
            tab[idx] = entry;
            return;
        }
        // entry->key == key never happens because of twoSum impl
        if (h2 == 1) {
            h2 = hash2(key);
        }
    }
}

static inline int32_t find(const int32_t key) {
    size_t h = hash(key);
    size_t h2 = 1;
    for (size_t i = 0; i < TAB_SZ; ++i) {
        size_t idx = (h + i * h2) % TAB_SZ;
        Entry *entry = tab[idx];
        if (!entry) {
            return -1;
        }
        if (entry->key == key) {
            return entry->value;
        } else if (h2 == 1) {
            h2 = hash2(key);
        }
    }
    return -1;
}

int *twoSum(const int *const nums,
            const int n,
            const int target,
            int *returnSize) {
    int *const res = (int *) malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < n; i++) {
        int32_t num = (int32_t)nums[i];
        int32_t complement = target - num;
        int32_t complement_idx = find(complement);
        if (complement_idx != -1) {
            res[0] = complement_idx;
            res[1] = (int32_t)i;
            goto EXIT;
        }
        insert((int32_t)nums[i], (int32_t)i);
    }
EXIT:
    clear();
    return res;
}
