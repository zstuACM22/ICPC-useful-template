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

int rk[MAX << 1];  // 索引 i 的后缀的排名
int sa[MAX];       // 排名 i 的后缀的索引, sa 与 rk 互为双射

void build(const char *s, int n) {
    static int rk_old[MAX << 1];
    static int sa_old[MAX];
    static int buk[MAX];
    int *rk = ::rk;
    int *old_rk = rk_old;
    int *sa = ::sa;
    int *old_sa = sa_old;
    memset(buk, 0, sizeof(buk));
    for (int i = 0; i < n; i++) {
        rk[i] = s[i];
        buk[rk[i]]++;
    }
    for (int i = 1; i < 128; i++) 
        buk[i] += buk[i - 1];
    for (int i = n - 1; i >= 0; i--) 
        sa[--buk[rk[i]]] = i;
    swap(old_rk, rk);
    rk[sa[0]] = 0;
    for (int i = 1, p = 0; i < n; i++) {
        if (old_rk[sa[i - 1]] != old_rk[sa[i]])
            p++;
        rk[sa[i]] = p;
    }
    for (int w = 1; w < n; w <<= 1) {
        memset(buk, 0, sizeof(buk));
        swap(old_sa, sa);
        for (int i = 0; i < n; i++) 
            buk[rk[old_sa[i] + w]]++;
        for (int i = 1; i < n; i++) 
            buk[i] += buk[i - 1];
        for (int i = n - 1; i >= 0; i--) 
            sa[--buk[rk[old_sa[i] + w]]] = old_sa[i];
        memset(buk, 0, sizeof(buk));
        swap(old_sa, sa);
        for (int i = 0; i < n; i++) 
            buk[rk[old_sa[i]]]++;
        for (int i = 1; i < n; i++) 
            buk[i] += buk[i - 1];
        for (int i = n - 1; i >= 0; i--) 
            sa[--buk[rk[old_sa[i]]]] = old_sa[i];
        // sort(sa, sa + n, [&](int x, int y) -> bool {
        //     return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        // });
        swap(old_rk, rk);
        rk[sa[0]] = 0;
        for (int i = 1, p = 0; i < n; i++) {
            if (old_rk[sa[i - 1]] != old_rk[sa[i]] or old_rk[sa[i - 1] + w] != old_rk[sa[i] + w])
                p++;
            rk[sa[i]] = p;
        }
    }
    memcpy(::rk, rk, sizeof(::rk));
    memcpy(::sa, sa, sizeof(::sa));
}