#include <inttypes.h>

/**
 * Exercise: https://leetcode.com/problems/minimum-falling-path-sum
 * Explanation: https://leetcode.com/problems/minimum-falling-path-sum/solutions/4594546/c-using-dp-beats-100-0-1-space-no-dynamic-allocation-no-input-mutation-explained/?submissionId=1150909672
 *
 * Constraints:
 * 
 * n == matrix.length == matrix[i].length
 * 1 <= n <= 100
 * -100 <= matrix[i][j] <= 100
 */

#define MAX_N 100

static const size_t MIN_SUM_BYTES = sizeof(int64_t) * MAX_N * MAX_N;
static int64_t min_sum[MAX_N][MAX_N];

static inline int64_t min2(int64_t a, int64_t b) {
    return a <= b ? a : b;
}

static inline int64_t min3(int64_t a, int64_t b, int64_t c) {
    return min2(min2(a, b), c);
}

static inline int64_t min_adjacent(const int64_t *const  row,
                                   const size_t col,
                                   const size_t n_cols) {
    int64_t mid = row[col];
    if (col != 0) {
        int64_t a = col != n_cols-1
            ? min3(row[col-1], mid, row[col+1])
            : min2(row[col-1], mid);
            return a;
    }
    return col != n_cols-1 ? min2(mid, row[col+1]) : mid;
}

// Precondition: n > 0
static inline int64_t min_arr(const int64_t *const a,
                              const size_t n) {
    int64_t min = a[0];
    for (size_t i = 1; i < n; i++) {
        int64_t curr = a[i];
        if (curr < min) {
            min = curr;
        }
    }
    return min;
}

int64_t minFallingPathSum(const int **const m,
                          const size_t n,
                          const size_t *const ignored) {
    for (size_t i = 0; i < n; i++) {
        min_sum[0][i] = m[0][i];
    }
    for (size_t i = 1; i < n; i++) {
        int *row = m[i];
        for (size_t j = 0; j < n; j++) {
            int cell_val = row[j];
            int64_t min_prev = min_adjacent(min_sum[i-1], j, n);
            min_sum[i][j] = cell_val + min_prev;
        }
    }
    int64_t res = min_arr(min_sum[n-1], n);
    memset(min_sum, 0, MIN_SUM_BYTES);
    return res;
}
