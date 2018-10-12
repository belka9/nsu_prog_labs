#include <stdio.h>
#include <mem.h>
#include <malloc.h>
#include <ctype.h>

#define MAX_LEN_ARR 45
#define MAX_LEN_NUM 15

long long power(long long a, long long exp) {
    long long solve = 1;
    for (long long i = 0; i < exp; i++) {
        solve *= a;
    }
    return solve;
}

long long charToInt(char ch) {
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

char intToChar(long long a) {
    if (a >= 0 && a <= 9)
        return (char) (a + '0');
    if (a >= 10 && a <= 15)
        return (char) (a + 'a' - 10);
    return -1;
}

long long tests(long long b1, long long b2, char *str) {
    if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16 || str[0] == '.' || str[strlen(str) - 1] == '.')
        return -1;
    long long k = 0;
    for (long long i = 0; i < strlen(str); i++) {
        str[i] = (char) tolower(str[i]);
        if (charToInt(str[i]) >= b1) {
            return -1;
        }
        if (str[i] == '.') {
            k += 1;
        }
    }
    if (k > 1)
        return -1;
    return 1;
}

long long decToDec(char *decPart, long long b1) {
    long long sum = 0;
    long long n = strlen(decPart);
    for (long long i = 0; i < n; i++) {
        sum += charToInt(decPart[i]) * power(b1, n - i - 1);
    }
    return sum;
}

double fracToDec(char *fracPart, long long b1) {
    double sum = 0;
    long long n = strlen(fracPart);
    for (long long i = 0; i < n; i++) {
        sum += (double) charToInt(fracPart[i]) / power(b1, i + 1);
    }
    return sum;
}

void decToB2AndPrint(long long dec, long long b2) {
    char arr[MAX_LEN_ARR] = {0};
    long long i = 0;
    while (dec >= b2) {
        arr[i] = intToChar(dec % b2);
        dec /= b2;
        i++;
    }
    arr[i] = intToChar(dec);
    for (; i >= 0; i--) {
        printf("%c", arr[i]);
    }
}

void fracToB2AndPrint(double frac, long long b2) {
    while (frac > 0) {
        frac *= b2;
        printf("%c", intToChar((long long) frac));
        frac -= (long long) frac;
    }
}

void solveAndPrint(long long b1, long long b2, char *str) {
    int posPoint = 0, n = strlen(str);
    char decPart[MAX_LEN_NUM] = {0};
    char fracPart[MAX_LEN_NUM] = {0};
    for (int i = 0; i < n; i++) {
        if (str[i] == '.')
            posPoint = i;
    }
    if (posPoint == 0) posPoint = n;
    for (long long i = 0; i < posPoint; i++) {
        decPart[i] = str[i];
    }
    for (long long i = posPoint + 1; i < n; i++) {
        fracPart[i - posPoint - 1] = str[i];
    }
    long long dec = decToDec(decPart, b1);
    double frac = fracToDec(fracPart, b1);
    decToB2AndPrint(dec, b2);
    if (posPoint < n) {
        printf(".");
        fracToB2AndPrint(frac, b2);
    }
}

int main() {
    int b1, b2;
    char str[MAX_LEN_NUM] = {0};
    scanf("%d%d%s", &b1, &b2, str);
    if (tests(b1, b2, str) == -1) {
        printf("bad input");
    } else {
        solveAndPrint(b1, b2, str);
    }
    return 0;
}