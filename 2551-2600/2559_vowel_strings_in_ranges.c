#include <inttypes.h>

// Exercise: https://leetcode.com/problems/count-vowel-strings-in-ranges/description/
// Solution: https://leetcode.com/problems/count-vowel-strings-in-ranges/solutions/6225290/beats-100-ok-time-where-k-n-on-space-laz-ta50/
//
// O(k) time, where k <= n
// O(n) space

#define PREFIX_SUM_THRESHOLD 513

static inline bool is_vowel(const char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static inline bool is_ok(const char *s) {
    const size_t n = strnlen(s, 40);
    return is_vowel(s[0]) && (n == 1 || is_vowel(s[n-1]));
}

typedef uint64_t BitsetBlock;
typedef BitsetBlock *Bitset;

static inline void bs_set(Bitset bs, const int idx) {
    const int i = idx / sizeof(BitsetBlock);
    BitsetBlock diff = ((BitsetBlock)1 << (idx % sizeof(BitsetBlock)));
    bs[i] |= diff;
}

static inline void bs_clear(Bitset bs, const int idx) {
    const int i = idx / sizeof(BitsetBlock);
    BitsetBlock diff = ~((BitsetBlock)1 << (idx % sizeof(BitsetBlock)));
    bs[i] &= diff;
}

static inline int bs_is_set(Bitset bs, const int idx) {
    const int i = idx / sizeof(BitsetBlock);
    return (bs[i] >> (idx % sizeof(BitsetBlock))) & 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *vowelStrings(
    char **words,
    const int words_size,
    int **queries,
    const int queries_size,
    const int const *query_cols, // always equal to 2
    int *return_size             // always equal to queries_size
) {
    *return_size = queries_size;
    int *ret = calloc(queries_size, sizeof(int));
    if (words_size == 0) return ret;

    Bitset seen = calloc(
        (words_size + sizeof(BitsetBlock) - 1) / sizeof(BitsetBlock),
        sizeof(BitsetBlock));

    if (words_size < PREFIX_SUM_THRESHOLD) {
        Bitset ok = calloc(
            (words_size + sizeof(BitsetBlock) - 1) / sizeof(BitsetBlock),
            sizeof(BitsetBlock));
        for (int i = 0; i < queries_size; i++) {
            const int const *q = queries[i];
            const int from = q[0];
            const int to = q[1];
            if (from < 0 || to >= words_size || from > to) {
                ret[i] = 0;
                continue;
            }
            for (int j = from; j <= to; j++) {
                if (bs_is_set(ok, j)) {
                    ret[i]++;
                    continue;
                }
                if (bs_is_set(seen, j)) continue;
                if (is_ok(words[j])) {
                    bs_set(ok, j);
                    ret[i]++;
                }
                bs_set(seen, j);
            }
        }
        free(ok);
    } else {
        int *prefix_sum = calloc(words_size, sizeof(int));
        for (int i = 0; i < queries_size; i++) {
            const int const *q = queries[i];
            const int from = q[0];
            const int to = q[1];
            if (from < 0 || to >= words_size || from > to) {
                ret[i] = 0;
                continue;
            }
            if (!bs_is_set(seen, to)) {
                int j = 0;
                if (bs_is_set(seen, from)) {
                    for (j = from; bs_is_set(seen, j) && j < to; j++);
                }
                for (; j <= to; j++) {
                    const int prev = j > 0 ? prefix_sum[j-1] : 0;
                    const int curr = is_ok(words[j]) ? 1 : 0;
                    prefix_sum[j] = prev + curr;
                    bs_set(seen, j);
                }
            }
            ret[i] = prefix_sum[to] - (from > 0 ? prefix_sum[from-1] : 0);
        }
        free(prefix_sum);
    }
    free(seen);
    return ret;
}
