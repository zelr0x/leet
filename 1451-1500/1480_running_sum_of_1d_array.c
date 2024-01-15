/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    size_t sz = numsSize * sizeof(int);
    int *res = malloc(sz);
    if (!res) return 0;
    *returnSize = numsSize;

    int *resStart = res;
    int sum = 0;
    while (numsSize-- > 0) {
        sum += *nums++;
        *res++ = sum;
    }
    return resStart;
}
