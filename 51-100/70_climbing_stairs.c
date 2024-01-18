#include <math.h>

/**
 * Exercise: https://leetcode.com/problems/climbing-stairs
 * Solution: https://leetcode.com/problems/climbing-stairs/solutions/4588840/c-math-only-beats-100-0ms-o-1-time-o-1-space-no-dp/?envType=daily-question&envId=2024-01-18
 */

const double SQRT5 = sqrt(5);

int climbStairs(const int n) {
    const int next_n = n + 1;
    const double fib_n = (pow((1 + SQRT5) / 2, next_n) - pow((1 - SQRT5) / 2, next_n)) / SQRT5;
    return round(fib_n);
}
