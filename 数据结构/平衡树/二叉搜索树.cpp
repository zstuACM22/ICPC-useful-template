// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 二叉搜索树
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

// 代码实现约定:
// tr[0].sum 始终为 0, 其余随意; tr[root].father 始终为 0; root == 0 表示空树, next == 0 表示无儿子
struct BST {
    int key;      // 键
    int cnt;      // 计数
    int father;   // 父节点
    int next[2];  // 左右子节点
    int sum;      // 子树求和
} tr[MAX];
int cnt_tr = 1;
int root = 0;

#define fa(idx) tr[idx].father
#define ls(idx) tr[idx].next[0]
#define rs(idx) tr[idx].next[1]
#define who(idx) ((idx) == rs(fa(idx)))  // 是否为父的右儿子

// 清空
void clear() {
    root = 0;
    memset(tr, 0, sizeof(BST) * cnt_tr);
    cnt_tr = 0;
}

// 维护子树求和 (单步)
inline void up(int idx) { tr[idx].sum = tr[ls(idx)].sum + tr[rs(idx)].sum + tr[idx].cnt; }

// 维护子树求和
inline void maintain(int idx) {
    while (idx) {
        up(idx);
        idx = fa(idx);
    }
}

typedef int iter;

// 建树, 将形成一棵平衡树, 0-index. 时间: O(nlogn)
pair<int, int> a[MAX];  // {key, cnt}
void build(int l, int r, int pre) {
    if (l > r) return;
    int nxt = cnt_tr++, mid = (l + r) / 2;
    tr[pre].next[a[mid].first > tr[pre].key] = nxt;
    tr[nxt].key = a[mid].first;
    tr[nxt].cnt = a[mid].second;
    tr[nxt].father = pre;
    build(l, mid - 1, nxt);
    build(mid + 1, r, nxt);
    if (nxt) up(nxt);
}
void build(int n) {
    if (n == 0) return;
    sort(a, a + n);  // 瓶颈
    int pre = -INF - 1, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first != pre) {
            pre = a[i].first;
            a[cnt++] = {pre, 0};
        }
        a[cnt - 1].second++;
    }
    build(0, cnt - 1, 0);
    root = 1;
}

// 遍历. 时间: O(n)
iter walk_list[MAX];
int walk_cnt = 0;
void walk(iter idx) {
    if (idx == 0) return;
    walk(ls(idx));
    walk_list[walk_cnt++] = idx;
    walk(rs(idx));
}

// 元素索引, 元素不存在返回 -1. 时间: O(logn)
iter find(int x) {
    if (root == 0)
        return -1;
    int idx = root;
    while (idx) {
        if (x == tr[idx].key)
            return idx;
        idx = tr[idx].next[x > tr[idx].key];
    }
    return -1;
}

// 最小元素索引, 空树返回 -1. 时间: O(logn)
iter mini(iter idx = root) {
    if (root == 0)
        return -1;
    while (ls(idx))
        idx = ls(idx);
    return idx;
}

// 最大元素索引, 空树返回 -1. 时间: O(logn)
iter maxi(iter idx = root) {
    if (root == 0)
        return -1;
    while (rs(idx))
        idx = rs(idx);
    return idx;
}

// 元素前驱索引. 特别地, 无前驱返回 -1, -1 前驱返回最大元素索引. 时间: O(logn)
iter pre(iter idx) {
    if (idx == -1)
        return maxi();
    if (ls(idx))
        return maxi(ls(idx));
    while (idx != root) {
        if (who(idx) == 1)
            return fa(idx);
        idx = fa(idx);
    }
    return -1;
}

// 元素后继索引. 特别地, 无后继返回 -1, -1 后继返回最小元素索引. 时间: O(logn)
iter nxt(iter idx) {
    if (idx == -1)
        return mini();
    if (rs(idx))
        return mini(rs(idx));
    while (idx != root) {
        if (who(idx) == 0)
            return fa(idx);
        idx = fa(idx);
    }
    return -1;
}

// 插入元素. 时间: O(logn)
void add(int x) {
    // case 1: 空树
    if (root == 0) {
        int nxt = cnt_tr++;
        tr[nxt].key = x;
        tr[nxt].cnt = 1;
        tr[nxt].father = 0;
        root = nxt;
        maintain(nxt);
        return;
    }
    int idx = root;
    while (true) {
        // case 2: 元素已存在
        if (x == tr[idx].key) {
            tr[idx].cnt++;
            maintain(idx);
            return;
        }
        // case 3: 元素不存在
        if (tr[idx].next[x > tr[idx].key] == 0) {
            int nxt = cnt_tr++;
            tr[idx].next[x > tr[idx].key] = nxt;
            tr[nxt].key = x;
            tr[nxt].cnt = 1;
            tr[nxt].father = idx;
            maintain(nxt);
            return;
        }
        idx = tr[idx].next[x > tr[idx].key];
    }
}

// 删除索引, 直接删除索引而非计数 -1. 时间: O(logn)
void del_idx(iter idx) {
    // case 1: idx 处在一条链 (没有左儿子) / idx 是叶子节点
    if (ls(idx) == 0) {
        tr[fa(idx)].next[who(idx)] = rs(idx);
        tr[rs(idx)].father = fa(idx);
        if (fa(idx) == 0)
            root = rs(idx);
        maintain(fa(idx));
        return;
    }
    // case 2: idx 处在一条链 (没有右儿子)
    if (rs(idx) == 0) {
        tr[fa(idx)].next[who(idx)] = ls(idx);
        tr[ls(idx)].father = fa(idx);
        if (fa(idx) == 0)
            root = ls(idx);
        maintain(fa(idx));
        return;
    }
    // case 3: 否则, 寻找后继交换后删除
    int pre = idx;
    idx = rs(idx);
    while (ls(idx)) {
        idx = ls(idx);
    }
    swap(tr[pre].key, tr[idx].key);
    swap(tr[pre].cnt, tr[idx].cnt);
    del_idx(idx);
}

// 删除元素, 元素不存在返回 -1. 时间: O(logn)
bool del(int x) {
    // case 1: 元素不存在
    if (root == 0)
        return false;
    int idx = root;
    while (idx) {
        if (x == tr[idx].key) {
            tr[idx].cnt--;
            if (tr[idx].cnt) {
                maintain(idx);
                return true;
            }
            // case 2: 元素存在
            del_idx(idx);
            return true;
        }
        idx = tr[idx].next[x > tr[idx].key];
    }
    return false;
}

// 元素 x 排名, x 不存在返回 -1. 1-index, 时间: O(logn)
int rk(int x) {
    if (root == 0)
        return -1;
    int idx = root, cnt = 0;
    while (idx) {
        if (x < tr[idx].key) {
            idx = ls(idx);
        } else {
            cnt += tr[ls(idx)].sum;
            if (x == tr[idx].key)
                return cnt + 1;
            cnt += tr[idx].cnt;
            idx = rs(idx);
        }
    }
    return -1;
}

// 排名 rk 索引, 总数不足 rk 返回 -1. 1-index, 时间: O(logn)
iter kth(int rk) {
    if (tr[root].sum < rk)
        return -1;
    int idx = root;
    while (true) {
        if (rk <= tr[ls(idx)].sum) {
            idx = ls(idx);
        } else {
            rk -= tr[ls(idx)].sum + tr[idx].cnt;
            if (rk <= 0)
                return idx;
            idx = rs(idx);
        }
    }
}

// 第一个大于等于 x 的元素索引, 不存在返回 -1. 时间: O(logn)
iter lower_bound(int x) {
    if (root == 0)
        return -1;
    int idx = root;
    while (true) {
        if (x == tr[idx].key)
            return idx;
        if (x < tr[idx].key) {
            if (ls(idx) == 0)
                return idx;
            idx = ls(idx);
        } else {
            if (rs(idx) == 0)
                return nxt(idx);
            idx = rs(idx);
        }
    }
}

// 第一个严格大于 x 的元素索引, 不存在返回 -1. 时间: O(logn)
iter upper_bound(int x) {
    if (root == 0)
        return -1;
    int idx = root;
    while (true) {
        if (x == tr[idx].key)
            return nxt(idx);
        if (x < tr[idx].key) {
            if (ls(idx) == 0)
                return idx;
            idx = ls(idx);
        } else {
            if (rs(idx) == 0)
                return nxt(idx);
            idx = rs(idx);
        }
    }
}