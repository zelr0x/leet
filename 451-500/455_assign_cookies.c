#include <stdlib.h>
#include <string.h>

/**
 * Exercise: https://leetcode.com/problems/assign-cookies/
 * Explanation: https://leetcode.com/problems/assign-cookies/solutions/4605908/c-beats-100-no-input-mutation-no-dynamic-memory/
 *
 * Constraints:
 * 1 <= g.length <= 3 * 10^4
 * 0 <= s.length <= 3 * 10^4
 * 1 <= g[i], s[j] <= 23^1 - 1
 */

#define MIN_MERGE 64
#define BUF_SZ 30000

static int g_buf[BUF_SZ];
static int s_buf[BUF_SZ];

static void merge(int *arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] >= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < len1) {
        arr[k++] = left[i++];
    }
    while (j < len2) {
        arr[k++] = right[j++];
    }
}

static void insertionsort(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static void timsort(int *arr, int n) {
    for (int i = 0; i < n; i += MIN_MERGE) {
        insertionsort(arr, i, i + MIN_MERGE - 1);
    }
    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = left + 2 * size - 1;
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

int findContentChildren(const int const* g, const int gn,
                        const int *const s, const int sn) {
    if (sn == 0) return 0;
    const size_t g_bytes = gn * sizeof(int);
    const size_t s_bytes = sn * sizeof(int);
    memcpy(g_buf, g, g_bytes);
    memcpy(s_buf, s, s_bytes);
    timsort(g_buf, gn);
    timsort(s_buf, sn);
    int res = 0;
    for (int si = 0, gi = 0; gi < gn && si < sn; gi++) {
        int greed = g_buf[gi];
        int size = s_buf[si];
        if (size >= greed) {
            res++;
            si++;
        }
    }
    memset(g_buf, 0, g_bytes);
    memset(s_buf, 0, s_bytes);
    return res;
}
