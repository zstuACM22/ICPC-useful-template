// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Splay
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

// 代码实现约定:
// tr[0].sum 始终为 0, 其余随意; tr[root].father 始终为 0; root == 0 表示空树, next == 0 表示无儿子
struct Splay {
    int key;      // 键
    int cnt;      // 计数
    int father;   // 父节点
    int next[2];  // 左右子节点
    int sum;      // 子树求和
} tr[MAX];        // 1-index
int root = 0;
int cnt_tr = 1;

// 清空
void clear() {
    root = 0;
    memset(tr, 0, sizeof(Splay) * cnt_tr);
    cnt_tr = 1;
}

// 维护子树求和, idx != 0
inline void up(int idx) { tr[idx].sum = tr[tr[idx].next[0]].sum + tr[tr[idx].next[1]].sum + tr[idx].cnt; }

// 为父的右儿子, idx != root and idx != 0
inline bool who(int idx) { return idx == tr[tr[idx].father].next[1]; }

// 旋转使 idx 上升, idx != root and idx != 0
inline void rotate(int idx) {
    bool w = who(idx);
    int f = tr[idx].father, ff = tr[f].father, s = tr[idx].next[not w];
    tr[ff].next[who(f)] = idx;
    tr[idx].father = ff;
    tr[f].next[w] = s;
    tr[s].father = f;
    tr[idx].next[not w] = f;
    tr[f].father = idx;
    up(f);
    up(idx);
}

// splay 核心操作, 分 zig / zig-zig / zig-zag, 所有指针移动后都要 splay. tar 表示 splay 到变为谁的子节点
inline void splay(int idx, int tar = 0) {
    for (int f = tr[idx].father; f != tar; f = tr[idx].father) {
        if (tr[f].father != tar)
            rotate(who(idx) == who(f) ? f : idx);
        rotate(idx);
    }
    if (tar == 0)
        root = idx;
}

typedef int iter;  // 索引, 避免与值混淆

// 建树, 0-index. 时间: O(nlogn)
int a[MAX];
void build(int n) {
    if (n == 0)
        return;
    sort(a, a + n);  // 瓶颈
    int pre = -INF - 1;
    for (int i = 0; i < n; i++) {
        if (a[i] == pre) {
            tr[cnt_tr - 1].cnt++;
        } else {
            tr[cnt_tr].key = a[i];
            tr[cnt_tr].cnt = 1;
            tr[cnt_tr - 1].next[1] = cnt_tr;
            tr[cnt_tr].father = cnt_tr - 1;
            cnt_tr++;
        }
        pre = a[i];
    }
    for (int i = cnt_tr - 1; i >= 1; i--)
        up(i);
    root = 1;
}

// 遍历. 时间: O(n)
iter walk_list[MAX];
int walk_cnt = 0;
void walk(iter idx) {
    if (idx == 0) 
        return;
    walk(tr[idx].next[0]);
    walk_list[walk_cnt++] = idx;
    walk(tr[idx].next[1]);
}

// 元素索引, 元素不存在返回 -1. 时间: O(logn)
iter find(int x) {
    if (root == 0)
        return -1;
    int idx = root;
    while (true) {
        if (x == tr[idx].key) {
            splay(idx);
            return idx;
        }
        if (tr[idx].next[x > tr[idx].key] == 0) {
            splay(idx);
            return -1;
        }
        idx = tr[idx].next[x > tr[idx].key];
    }
}

// 最小元素索引, 空树返回 -1. 时间: O(logn)
iter mini() {
    if (root == 0)
        return -1;
    int idx = root;
    while (tr[idx].next[0])
        idx = tr[idx].next[0];
    splay(idx);
    return idx;
}

// 最大元素索引, 空树返回 -1. 时间: O(logn)
iter maxi() {
    if (root == 0)
        return -1;
    int idx = root;
    while (tr[idx].next[1])
        idx = tr[idx].next[1];
    splay(idx);
    return idx;
}

// 元素前驱索引. 特别地, 无前驱返回 -1, -1 前驱返回最大元素索引. 时间: O(logn)
iter pre(iter idx) {
    if (idx == -1)
        return maxi();
    splay(idx);
    idx = tr[idx].next[0];
    if (idx == 0)
        return -1;
    while (tr[idx].next[1])
        idx = tr[idx].next[1];
    splay(idx);
    return idx;
}

// 元素后继索引. 特别地, 无后继返回 -1, -1 后继返回最小元素索引. 时间: O(logn)
iter nxt(iter idx) {
    if (idx == -1)
        return mini();
    splay(idx);
    idx = tr[idx].next[1];
    if (idx == 0)
        return -1;
    while (tr[idx].next[0])
        idx = tr[idx].next[0];
    splay(idx);
    return idx;
}

// 插入元素. 时间: O(logn)
void add(int x) {
    // case 1: 空树
    if (root == 0) {
        int nxt = cnt_tr++;
        tr[nxt].key = x;
        tr[nxt].cnt = 1;
        tr[nxt].father = 0;
        up(nxt);
        splay(nxt);
        return;
    }
    int idx = root;
    while (true) {
        // case 2: 元素已存在
        if (x == tr[idx].key) {
            tr[idx].cnt++;
            up(idx);
            splay(idx);
            return;
        }
        // case 3: 元素不存在
        if (tr[idx].next[x > tr[idx].key] == 0) {
            int nxt = cnt_tr++;
            tr[idx].next[x > tr[idx].key] = nxt;
            tr[nxt].key = x;
            tr[nxt].cnt = 1;
            tr[nxt].father = idx;
            up(nxt);
            up(idx);
            splay(nxt);
            return;
        }
        idx = tr[idx].next[x > tr[idx].key];
    }
}

// 删除元素, 元素不存在返回 -1. 时间: O(logn)
bool del(int x) {
    // case 1: 元素不存在 (同时 splay 为根)
    if (find(x) == -1)
        return -1;
    tr[root].cnt--;
    // case 2: 无需移除点
    if (tr[root].cnt)
        return true;
    // case 3: 移除后左子树为空
    if (tr[root].next[0] == 0) {
        root = tr[root].next[1];
        tr[root].father = 0;
        if (root)
            up(root);
        return true;
    }
    // case 4: 移除后左子树非空
    int ri = tr[root].next[1];
    root = tr[root].next[0];
    tr[root].father = 0;
    maxi();
    tr[root].next[1] = ri;
    tr[ri].father = root;
    up(root);
    return true;
}

// 元素 x 排名, x 不存在返回 -1. 1-index, 时间: O(logn)
int rk(int x) {
    if (find(x) == -1)
        return -1;
    return tr[tr[root].next[0]].sum + 1;
}

// 排名 rk 索引, 总数不足 rk 返回 -1. 1-index, 时间: O(logn)
iter kth(int rk) {
    if (tr[root].sum < rk)
        return -1;
    int idx = root, cnt = 0;
    while (true) {
        if (rk <= tr[tr[idx].next[0]].sum) {
            idx = tr[idx].next[0];
        } else {
            rk -= tr[tr[idx].next[0]].sum + tr[idx].cnt;
            if (rk <= 0) {
                splay(idx);
                return idx;
            }
            idx = tr[idx].next[1];
        }
    }
}

// 第一个大于等于 x 的元素索引, 不存在返回 -1. 时间: O(logn)
iter lower_bound(int x) {
    if (root == 0)
        return -1;
    find(x);
    if (x <= tr[root].key)
        return root;
    return nxt(root);
}

// 第一个严格大于 x 的元素索引, 不存在返回 -1. 时间: O(logn)
iter upper_bound(int x) {
    if (root == 0)
        return -1;
    find(x);
    if (x < tr[root].key)
        return root;
    return nxt(root);
}
