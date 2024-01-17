#include <stdint.h>

/**
 * https://leetcode.com/problems/unique-number-of-occurrences
 *
 * Constraints:
 * 1 <= n <= 1000
 * -1000 <= arr[i] <= 1000
 */

 #define SEEN_SZ 2001
 #define UQ_SZ 1001

static int16_t seen[SEEN_SZ];
static uint16_t uq[UQ_SZ];

// Assumes pos and neg ranges are of the same size.
static inline size_t seen_idx(int n) {
    return n >= 0 ? n : n + SEEN_SZ;
}

bool uniqueOccurrences(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        size_t si = seen_idx(num);
        int16_t occ = ++seen[si];
        if (occ > 1) {
            --uq[occ-1];
        }
        ++uq[occ];
    }
    bool res = true;
    for (int i = 1; i < 1001; i++) {
        if (uq[i] > 1) {
            res = false;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        size_t si = seen_idx(num);
        uint16_t occ = seen[si];
        seen[si] = 0;
        uq[occ] = 0;
    }
    return res;
}
