// Exercise: https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/
//
// O(N) time, O(1) space
int maxScore(char *s) {
    int res = 0;
    int n = 0;
    int ones = 0;
    {
        int i = 0;
        char c;
        while ((c = s[i++]) != '\0') {
            if (c == '1') ones++;
            n++;
        }
    }

    int zeroes = 0;
    for (int i = 0; i < n-1; i++) {
        char c = s[i];
        if (c == '0') {
            zeroes++;
        } else if (c == '1') {
            ones--;
        }
        int curr = zeroes + ones;
        if (curr > res) {
            res = curr;
        }
    }
    return res;
}
