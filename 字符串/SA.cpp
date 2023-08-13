// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 后缀数组 (SA, SuffixArray)
// 时间: O(nlogn) (基数排序)
const int MAX = 100005;

int rk[MAX];  // 索引 i 的后缀的排名
int sa[MAX];  // 排名 i 的后缀的索引, sa 与 rk 互为双射
int oldrk[MAX << 1];
int oldsa[MAX];
int buk[MAX];

inline bool cmp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] and oldrk[x + w] == oldrk[y + w];
}

void build(const char *s, int n) {
    int m = 128, p = 0;  // 值域优化, 平均情况下优化力度很大
    memset(buk, 0, sizeof(int) * m);
    for (int i = 0; i < n; i++) {
        rk[i] = s[i];
        buk[rk[i]]++;
    }
    for (int i = 1; i < m; i++)
        buk[i] += buk[i - 1];
    for (int i = n - 1; i >= 0; i--)
        sa[--buk[rk[i]]] = i;
    for (int w = 1; p < n; w <<= 1, m = p) {
        for (p = 0; p < w; p++)
            oldsa[p] = n - 1 - p;
        for (int i = 0; i < n; i++)
            if (sa[i] >= w)
                oldsa[p++] = sa[i] - w;
        memset(buk, 0, sizeof(int) * m);
        for (int i = 0; i < n; i++)
            buk[rk[oldsa[i]]]++;
        for (int i = 1; i < m; i++)
            buk[i] += buk[i - 1];
        for (int i = n - 1; i >= 0; i--)
            sa[--buk[rk[oldsa[i]]]] = oldsa[i];
        memcpy(oldrk, rk, sizeof(int) * n);
        p = 0;
        rk[sa[0]] = p++;
        for (int i = 1; i < n; i++)
            rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p - 1 : p++;
    }
}