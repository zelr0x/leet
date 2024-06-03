static inline int toInt(char c) {
    switch (c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
    }
}

int romanToInt(char* s) {
    int acc = 0;
    int prev = 0;
    int curr;
    char c;
    while ((c = *s++) != '\0') {
        curr = toInt(c);
        acc += curr;
        if (prev < curr) {
            acc -= prev + prev;
        }
        prev = curr;
    }
    return acc;
}
