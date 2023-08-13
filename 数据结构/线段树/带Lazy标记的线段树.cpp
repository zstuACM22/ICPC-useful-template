// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 带 lazy 标记的线段树 - 以 区间求和-区间修改 为例. 局限性: 大常数
// https://www.luogu.com.cn/problem/P3372
const int MAX = 100005;

int n;
int a[MAX];  // 1-index 原始数组
struct ST {
    int sum;   // 求和
    int lazy;  // 懒标记
} tr[MAX << 2];

#define ls(idx) ((idx) * 2)      // 返回左子节点索引
#define rs(idx) ((idx) * 2 + 1)  // 返回右子节点索引

// 状态合并方程
void up(int idx, int left, int right) {
    tr[idx].sum = tr[ls(idx)].sum + tr[rs(idx)].sum;
}

// 标记传递方程
void down(int idx, int left, int right) {
    int mid = left + right >> 1;
    tr[ls(idx)].sum += tr[idx].lazy * (mid - left + 1);
    tr[ls(idx)].lazy += tr[idx].lazy;
    tr[rs(idx)].sum += tr[idx].lazy * (right - mid);
    tr[rs(idx)].lazy += tr[idx].lazy;
    tr[idx].lazy = 0;
}

// 建树. 时间: O(n)
void build(int idx, int left, int right) {
    if (left == right) {
        tr[idx].sum = a[left];
        tr[idx].lazy = 0;
        return;
    }
    int mid = left + right >> 1;
    build(ls(idx), left, mid);
    build(rs(idx), mid + 1, right);
    up(idx, left, right);
}
void build() { build(1, 1, n); }

// 清空标记并导出. 时间: O(n)
void load(int idx, int left, int right) {
    if (left == right) {
        a[left] = tr[idx].sum;
        return;
    }
    down(idx, left, right);
    int mid = left + right >> 1;
    load(ls(idx), left, mid);
    load(rs(idx), mid + 1, right);
}

// 区间修改. 时间: O(logn)
void modify(int idx, int left, int right, int l, int r, int val) {
    if (l <= left and right <= r) {
        tr[idx].sum += val * (right - left + 1);
        tr[idx].lazy += val;
        return;
    }
    down(idx, left, right);
    int mid = left + right >> 1;
    if (l <= mid) modify(ls(idx), left, mid, l, r, val);
    if (mid < r) modify(rs(idx), mid + 1, right, l, r, val);
    up(idx, left, right);
}
void modify(int l, int r, int val) { return modify(1, 1, n, l, r, val); }

// 区间询问. 时间: O(logn)
int query(int idx, int left, int right, int l, int r) {
    int res = 0;
    if (l <= left and right <= r) {
        return tr[idx].sum;
    }
    down(idx, left, right);
    int mid = left + right >> 1;
    if (l <= mid) res += query(ls(idx), left, mid, l, r);
    if (mid < r) res += query(rs(idx), mid + 1, right, l, r);
    return res;
}
int query(int l, int r) { return query(1, 1, n, l, r); }