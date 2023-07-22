// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 分块 - 以 区间求和-区间修改 为例. 时间: O(n^0.5) + 预处理: O(n) + 后处理: O(n), 内存: O(n)
// 0-index
const int MAX = 100005;
const int SQR = 320;

int a[MAX];
int siz;
int block[SQR][SQR];
int sum[SQR] = {0};
int lazy[SQR] = {0};

void build(int n) {
    siz = sqrt(n);
    for (int i = 0; i < n; i++) {
        block[i / siz][i % siz] = a[i];
        sum[i / siz] += a[i];
    }
}

void load(int n) {
    siz = sqrt(n);
    for (int i = (n - 1) / siz; i >= 0; i--) {
        for (int j = 0; j < siz; j++) {
            block[i][j] += lazy[i];
            a[i * siz + j] = block[i][j];
        }
        lazy[i] = 0;
    }
}

void modify(int l, int r, int val) {
    int ll = (l + siz - 1) / siz;
    int dl = (l + siz - 1) % siz + 1;
    int rr = (r + 1) / siz - 1;
    int dr = (r + 1) % siz - 1;
    for (int i = dl; i < siz; i++)
        block[ll - 1][i] += val;
    sum[ll - 1] += (siz - dl) * val;
    for (int i = ll; i <= rr; i++) {
        sum[i] += siz * val;
        lazy[i] += val;
    }
    for (int i = 0; i <= dr; i++)
        block[rr + 1][i] += val;
    sum[rr + 1] += (dr + 1) * val;
}

int query(int l, int r) {
    int ll = (l + siz - 1) / siz;
    int dl = (l + siz - 1) % siz + 1;
    int rr = (r + 1) / siz - 1;
    int dr = (r + 1) % siz - 1;
    int res = 0;
    for (int i = dl; i < siz; i++)
        res += block[ll - 1][i] + lazy[ll - 1];
    for (int i = ll; i <= rr; i++)
        res += sum[i];
    for (int i = 0; i <= dr; i++)
        res += block[rr + 1][i] + lazy[rr + 1];
    return res;
}