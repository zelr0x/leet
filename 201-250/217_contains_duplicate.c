#include <stdlib.h>

// Exercise: https://leetcode.com/problems/contains-duplicate/
// Solution: https://leetcode.com/problems/contains-duplicate/solutions/6241080/beats-100-0ms-10mb-optimized-hybrid-approach-c/

// These thresholds ensure optimal performance while not going above 10MB.
#define LINEAR_MAX_THRESHOLD 8
#define ISORT_MAX_THRESHOLD 256
#define VAL_DIFF_HASH_MAX_THRESHOLD 2500000
#define FNV_HASH_MAX_THRESHOLD 215000
// By exercise invariant values don't exceed 10**9 or -10**9
// so INT_MIN is fine as long as int is 32 bits or wider,
// which is implied by the same invariant.
#define SENTINEL INT_MIN

// Linear sort solution.
static inline bool constains_dup_linear(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) return true;
        }
    }
    return false;
}

// Insertion sort solution.
static inline bool contains_dup_isort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        if (j >= 0 && arr[j] == key) {
            return true;
        }
    }
    return false;
}

// Value-diff-based hash table (array of int) solution.
// The memory footprint can be significantly optimized by using a bitset,
// but that will result in performance decrease. Can be used as the next
// threshold before the proper hashset though.
static inline bool contains_dup_arr(int *arr, int n, int min, int max) {
    int cap = max - min + 1;
    int *set = (int *)malloc(cap * sizeof(int));
    for (int i = 0; i < n; i++) {
        int x = arr[i];
        int idx = x - min;
        if (++set[idx] > 1) {
            free(set);
            return true;
        }
    }
    return false;
}

// Normal hash table (array of intrusive lists) solution.
typedef struct IntrIntList {
    int data;
    struct IntrIntList *next;
} IntrIntList;

static inline uint32_t hash_int_fnv1a(int key) {
    const uint32_t offset_basis = 2166136261U;
    const uint32_t fnv_prime = 16777619U;
    uint32_t hash = offset_basis;
    uint32_t unsigned_key = (uint32_t)key;
    for (int i = 0; i < 4; i++) {
        hash ^= (unsigned_key & 0xFF);
        hash *= fnv_prime;
        unsigned_key >>= 8;
    }
    return hash;
}

static inline bool contains_dup_hashset(int *arr, int n) {
    int cap = n * 2;
    IntrIntList *set = (IntrIntList *)malloc(cap * sizeof(IntrIntList));
    for (int i = 0; i < cap; i++) {
        set[i].data = SENTINEL;
        set[i].next = NULL;
    }
    bool ret = false;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        uint32_t hash = hash_int_fnv1a(num);
        uint32_t idx = hash % cap;
        IntrIntList e = set[idx];
        if (e.data == SENTINEL) {
            set[idx].data = num;
            set[idx].next = NULL;
            continue;
        }
        if (e.data == num) {
            ret = true;
            goto end;
        }
        IntrIntList *node = &set[idx];
        while (true) {
            if (node->data == num) {
                ret = true;
                goto end;
            }
            if (node->next == NULL) {
                IntrIntList *new_node = (IntrIntList *)malloc(sizeof(IntrIntList));
                new_node->data = num;
                new_node->next = NULL;
                node->next = new_node;
                break;
            }
            node = node->next;
        }
    }
end:
    for (int i = 0; i < cap; i++) {
        IntrIntList *node = set[i].next;
        while (node != NULL) {
            IntrIntList *t = node;
            node = node->next;
            free(t);
        }
    }
    free(set);
    return ret;
}

// Quicksort solution. This is the only solution that is not optimized
// with early return on duplicate, but this is not used for inputs in
// this exercise. This is just to highlight that at some threshold it's
// essential to switch from a hashset to a faster sort if we want to stay
// within the memory bounds.
static inline int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

static inline bool contains_dup_qsort(int *arr, int n) {
    qsort(arr, n, sizeof(int), cmp_int);
    int prev = arr[0];
    for (int i = 1; i < n; i++) {
        int curr = arr[i];
        if (curr == prev) return true;
        prev = curr;
    }
    return false;
}

bool containsDuplicate(int *nums, const int n) {
    if (n < 1) return false;
    if (n <= LINEAR_MAX_THRESHOLD) {
        return constains_dup_linear(nums, n);
    }
    if (n <= ISORT_MAX_THRESHOLD) {
        return contains_dup_isort(nums, n);
    }
    if (n > FNV_HASH_MAX_THRESHOLD) {
        contains_dup_qsort(nums, n);
    }
    int min = INT_MAX;
    int max = INT_MIN;    
    for (int i = 0; i < n; i++) {
        int x = nums[i];
        if (x == min || x == max) return true;
        if (x < min) min = x;
        if (x > max) max = x;
    }
    if ((max-min) < VAL_DIFF_HASH_MAX_THRESHOLD) {
        return contains_dup_arr(nums, n, min, max);
    }
    return contains_dup_hashset(nums, n);
}
