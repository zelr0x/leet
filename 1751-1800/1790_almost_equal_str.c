#include <stddef.h>
#include <stdbool.h>

// Exercise: https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/
bool areAlmostEqual(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return false;
    char c1, c2;
    int d1 = -1, d2 = -1;
    for (int i = 0; ; i++) {
        c1 = s1[i];
        c2 = s2[i];
        bool z1 = c1 == '\0';
        bool z2 = c2 == '\0';
        if (z1 || z2) {
            if (!(z1 && z2)) return false;
            break;
        }
        if (c1 != c2) {
            if (d1 == -1) {
                d1 = i;
            } else if (d2 == -1) {
                d2 = i;
            } else {
                return false;
            }
        }
    }
    if (d1 == -1 || d2 == -1) return d1 == d2;
    return s1[d1] == s2[d2] && s1[d2] == s2[d1];
}
