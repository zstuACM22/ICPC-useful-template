// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 笛卡尔树 - Useless
// 唯一且即是二叉搜索树又是堆, 这里以小顶堆为例
const int MAX = 10000005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

struct CartTree {
    int val;      // 值
    int next[2];  // 子节点
} tr[MAX];
int root = 0;

// 建树, 1-index. 时间: O(n)
int a[MAX];
int stk[MAX];
int cnt_stk = 0;
void build(int n) {
    a[0] = -INF - 1;
    stk[cnt_stk++] = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = cnt_stk;
        while (cnt_stk and a[stk[cnt_stk - 1]] > a[i])
            cnt_stk--;
        tr[stk[cnt_stk - 1]].next[1] = i;
        if (cnt_stk < tmp)
            tr[i].next[0] = stk[cnt_stk];
        stk[cnt_stk++] = i;
        tr[i].val = a[i];
    }
    root = tr[0].next[1];
}