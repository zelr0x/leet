#include <limits.h>

/**
 * https://leetcode.com/problems/richest-customer-wealth
 */
int maximumWealth(const int **const accounts,
                  const int accountsSize,
                  const int *const accountsColSize) {
    long max = LONG_MIN;
    for (int i = 0; i < accountsSize; i++) {
        const int *const clientAccounts = accounts[i];
        const int nAccounts = accountsColSize[i];
        long clientTotal = 0;
        for (int j = 0; j < nAccounts; j++) {
            clientTotal += clientAccounts[j];
        }
        if (clientTotal > max) {
            max = clientTotal;
        }
    }
    return max;
}
