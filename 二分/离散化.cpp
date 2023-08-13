// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 离散化
const int MAX = 100005;

int a[MAX];
int M[MAX];
int cntM = 0;
int arcM(int x) { return lower_bound(M, M + cntM, x) - M; }

void build(int n) {
    for (int i = 0; i < n; i++)
        M[cntM++] = a[i];
    sort(M, M + cntM);
    cntM = unique(M, M + cntM) - M;
}