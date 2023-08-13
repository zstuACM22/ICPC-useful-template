// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAX = 1000005;
int nxt[MAX];  // 最长公共真前后缀

// KMP 字符串匹配(懒惰). s: 文本, pattern: 模式串, n: 文本长度, m: 模式串长度. 返回: 匹配首索引.
int kmp_lazy(const char *s, const char *pattern, int n, int m) {
    s--;
    pattern--; 
    nxt[0] = 0, nxt[1] = 0;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j and pattern[i] != pattern[j + 1]) j = nxt[j];
        if (pattern[i] == pattern[j + 1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j and s[i] != pattern[j + 1]) j = nxt[j];
        if (s[i] == pattern[j + 1]) j++;
        if (j == m) return i - j;
    }
    return -1;
}

// KMP 字符串匹配(贪婪). s: 文本, pattern: 模式串, n: 文本长度, m: 模式串长度, res: 结果数组. 返回: 结果数量.
int kmp_greedy(const char *s, const char *pattern, int n, int m, int res[]) {
    int cnt = 0;
    s--;
    pattern--;
    nxt[0] = 0, nxt[1] = 0;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j and pattern[i] != pattern[j + 1]) j = nxt[j];
        if (pattern[i] == pattern[j + 1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j and s[i] != pattern[j + 1]) j = nxt[j];
        if (s[i] == pattern[j + 1]) j++;
        if (j == m) {
            res[cnt++] = i - j;
            j = nxt[j];
        }
    }
    return cnt;
}