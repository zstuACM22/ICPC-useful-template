// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 带权线段树 - 以 计数小于x-单点修改 为例. 局限性: 不离散数域决定内存, 离散化或将约束修改
const int MAX = 100005;

struct SegmentTree {
    int left;
    int right;
    int tot = 0;  // Attention: 别忘了设置初值
} node[MAX * 4];  // 1-index

#define ls(idx) (idx * 2)
#define rs(idx) (idx * 2 + 1)  // 返回右子节点

// 向上维护, 状态合并方程  // Attention
SegmentTree &merge_up(SegmentTree &father, const SegmentTree &left, const SegmentTree &right) {
    father.tot = left.tot + right.tot;
    return father;
}

// 建树
void build(int l, int r, int idx) {
    if (l == r) {
        node[idx].left = l;
        node[idx].right = l;
        return;
    }
    int li = ls(idx), ri = rs(idx), mid = (l + r) / 2;
    build(l, mid, li);
    build(mid + 1, r, ri);
    node[idx].left = node[li].left;
    node[idx].right = node[ri].right;
    merge_up(node[idx], node[li], node[ri]);
}
void build(int n) { build(1, n, 1); }

// 单点插入  // Attention
void insert(int x, int idx) {
    if (x == node[idx].left and node[idx].right == x) {
        node[idx].tot++;
        return;
    }
    int li = ls(idx), ri = rs(idx), mid = (node[idx].left + node[idx].right) / 2;
    if (x <= mid)
        insert(x, li);
    else
        insert(x, ri);
    merge_up(node[idx], node[li], node[ri]);
}
void insert(int x) { insert(x, 1); }

// 区间查询  // Attention
int query(int x, int idx) {
    if (node[idx].left == node[idx].right)
        return node[idx].tot;
    int li = ls(idx), ri = rs(idx), mid = (node[idx].left + node[idx].right) / 2;
    if (x <= mid)
        return query(x, li);
    else
        return node[li].tot + query(x, ri);
}