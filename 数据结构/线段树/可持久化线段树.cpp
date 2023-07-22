// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 可持续化线段树(主席树) - 以 计数区间第k小 为例. 时间: O(logn) + 预处理: O(n), 内存: O(4n+3i+ilogn)
const int MAXI = 30005;
const int MAXN = 30005;
const int LOGN = 15;

int now_id = 0;
int len_version = 0;
struct Version {
    int id;
    int left;   // 左子版本
    int right;  // 右子版本
    int tot;
} version[MAXI * (LOGN + 3)];  // 1-index
struct SegmentTree {
    int left;
    int right;
    vector<int> version;  // Attention: 别忘了设置初值
} node[MAXN * 4];         // 1-index

#define ls(idx) (idx * 2)
#define rs(idx) (idx * 2 + 1)  // 返回右子节点

// 建树
void build(int l, int r, int idx) {
    if (l == r) {
        node[idx].left = l;
        node[idx].right = l;
        version[++len_version] = {0, 0, 0, 0};
        node[idx].version.push_back(len_version);
        return;
    }
    int li = ls(idx), ri = rs(idx), mid = (l + r) / 2;
    build(l, mid, li);
    build(mid + 1, r, ri);
    node[idx].left = node[li].left;
    node[idx].right = node[ri].right;
    version[++len_version] = {0, node[li].version.back(), node[ri].version.back(), 0};
    node[idx].version.push_back(len_version);
}
void build(int n) { build(1, n, 1); }

// 单点插入  // Attention
void insert(int x, int idx) {
    if (x == node[idx].left and node[idx].right == x) {
        version[++len_version] = {now_id, 0, 0, version[node[idx].version.back()].tot + 1};
        node[idx].version.push_back(len_version);
        return;
    }
    int li = ls(idx), ri = rs(idx), mid = (node[idx].left + node[idx].right) / 2;
    if (x <= mid)
        insert(x, li);
    else
        insert(x, ri);
    version[++len_version] = {now_id, node[li].version.back(), node[ri].version.back(), version[node[idx].version.back()].tot + 1};
    node[idx].version.push_back(len_version);
}
void insert(int x) {
    now_id++;
    insert(x, 1);
}

// 区间查询  // Attention
int search(const SegmentTree &node, int x) {
    int l = 0, r = node.version.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (version[node.version[mid]].id <= x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return node.version[r];
}
int query(int l, int r, int k, int idx, int lv, int rv) {
    if (node[idx].left == node[idx].right)
        return node[idx].left;
    int li = ls(idx), ri = rs(idx), mid = (node[idx].left + node[idx].right) / 2;
    int tot = version[version[rv].left].tot - version[version[lv].left].tot;
    if (k <= tot)
        return query(l, r, k, li, version[lv].left, version[rv].left);
    else
        return query(l, r, k - tot, ri, version[lv].right, version[rv].right);
}
int query(int l, int r, int k) {
    return query(l, r, k, 1, search(node[1], l - 1), search(node[1], r));
}