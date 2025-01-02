#include <stdlib.h>

// Exercise: https://leetcode.com/problems/duplicate-zeros/description/
//
// Single pass solution optimized for larger inputs with sparser distribution of zero sequences of any lengths.
// O(k), where k <= n time
// O(1) space

#define MEMMOVE_THRESHOLD_GT 8
#define MEMSET_THRESHOLD_GT 8

static inline void shift(int *src, int *dst, int cnt) {
    if (cnt > MEMMOVE_THRESHOLD_GT) {
        memmove(dst, src, cnt * sizeof(int));
        return;
    }
    for (int i = cnt - 1; i >= 0; i--) {
        dst[i] = src[i];
    }
}

static inline void zero(int *arr, int cnt) {
    if (cnt > MEMSET_THRESHOLD_GT) {
        memset(arr, 0, cnt * sizeof(int));
        return;
    }
    for (int i = 0; i < cnt; i++) {
        arr[i] = 0;
    }
}

void duplicateZeros(int *arr, int n) {
    int zero_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            zero_cnt++;
            continue;
        }
        if (zero_cnt == 0) continue;
        int si = i;
        int di = si + zero_cnt;
        if (di >= n) {
            zero(&arr[si], n-si);
            return;
        }
        shift(&arr[si], &arr[di], n - di);
        zero(&arr[si], zero_cnt);
        zero_cnt = 0;
        i = di;
    }
}
