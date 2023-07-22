// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

inline bool isblank(char c) { return c == ' ' or c == '\t' or c == '\r' or c == '\n' or c == '\0'; }

// 快读. __int128_t 类型必须使用此函数读取.
inline int read(int &x) {
    int ans = 0;
    bool f = false;
    char c = getchar();
    while (not isdigit(c)) {
        if (c == '-')
            f = true;
        c = getchar();
    }
    while (isdigit(c)) {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return x = f ? -ans : ans;
}

// 快读. 字符串快读
inline int read(char *s) {
    int cnt = 0;
    char c = getchar();
    while (not isblank(c)) {
        s[cnt++] = c;
        c = getchar();
    }
    s[cnt] = 0;
    return cnt;
}

// 快写. __int128_t 类型必须使用此函数打印.
inline void __write(int x) {
    if (x > 9)
        __write(x / 10);
    putchar(x % 10 + '0');
}
inline void write(int x) {
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    __write(x);
    putchar('\n');
}

// 快写. 字符串快写
inline void write(char *s) {
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
    putchar('\n');
}