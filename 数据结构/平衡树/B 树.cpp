// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// B 树 - Useless
// B 树适用于高频磁盘访问, 如数据库
// 由于 B 树未保证索引与键是静态绑定的, 所有对外接口均不返回索引
const int MAX = 100005;

// 代码实现约定:
// tr[0].keys, tr[0].sum 始终为 0, 其余随意; tr[root].father 始终为 0; root == 0 表示空树, next == 0 表示无儿子
const int ORDER = 5;                 // B 树的阶, >= 3
const int ULIMIT = ORDER - 1;        // 节点限制的最大键数
const int LLIMIT = (ORDER - 1) / 2;  // 节点限制的最小键数
struct Pair {
    int key;  // 键
    int cnt;  // 计数
};
struct BTree {
    int keys;             // 键数
    Pair pair[ORDER];     // 键值对
    int father;           // 父节点
    int next[ORDER + 1];  // 子节点
    int sum;              // 子树求和
} tr[MAX];
int cnt_tr = 1;
int root = 0;

#define fa(idx) tr[idx].father            // 父节点
#define leaf(idx) (tr[idx].next[0] == 0)  // 是否为叶子节点

// 清空
void clear() {
    root = 0;
    memset(tr, 0, sizeof(BTree) * cnt_tr);
    cnt_tr = 1;
}

// 维护子树求和 (单步). idx != 0
inline void up(int idx) {
    int res = 0;
    for (int i = tr[idx].keys - 1; i >= 0; i--)
        res += tr[idx].pair[i].cnt;
    for (int i = tr[idx].keys; i >= 0; i--)
        res += tr[tr[idx].next[i]].sum;
    tr[idx].sum = res;
}

// 维护子树求和
inline void maintain(int idx) {
    while (idx) {
        up(idx);
        idx = fa(idx);
    }
}

// 节点 idx 中第一个大于等于 x 的键索引, 找不到返回 tr[idx].keys
inline int find_key(int idx, int x) {
    int i = 0, keys = tr[idx].keys;
    for (; i < keys; i++)
        if (x <= tr[idx].pair[i].key)
            return i;
    return i;
}

// 向下查找一步, 查找结束返回 {true, 第一个大于等于的键索引}, 否则返回 {false, 下一个节点索引}
inline pair<bool, int> find_next(int idx, int x) {
    if (leaf(idx))  // case 1: 当前节点为叶子节点
        return {true, find_key(idx, x)};
    for (int i = 0; i < tr[idx].keys; i++) {
        if (x == tr[idx].pair[i].key)
            return {true, i};  // case 2: 查找的键为当前节点的一个键
        if (x < tr[idx].pair[i].key)
            return {false, tr[idx].next[i]};  // case 3: 查找的键在下一节点
    }
    return {false, tr[idx].next[tr[idx].keys]};
}

// 插入键及其左儿子
inline void add_key_and_left_son(int idx, int pos, const Pair &p, int nxt) {
    int keys = tr[idx].keys;
    memmove(tr[idx].pair + pos + 1, tr[idx].pair + pos, sizeof(Pair) * (keys - pos));
    memmove(tr[idx].next + pos + 1, tr[idx].next + pos, sizeof(int) * (keys - pos + 1));
    tr[idx].pair[pos] = p;
    tr[idx].next[pos] = nxt;
    fa(nxt) = idx;
    tr[idx].keys++;
}

// 插入键及其右儿子
inline void add_key_and_right_son(int idx, int pos, const Pair &p, int nxt) {
    int keys = tr[idx].keys;
    memmove(tr[idx].pair + pos + 1, tr[idx].pair + pos, sizeof(Pair) * (keys - pos));
    memmove(tr[idx].next + pos + 2, tr[idx].next + pos + 1, sizeof(int) * (keys - pos));
    tr[idx].pair[pos] = p;
    tr[idx].next[pos + 1] = nxt;
    fa(nxt) = idx;
    tr[idx].keys++;
}

// 删除键及其左儿子
inline void del_key_and_left_son(int idx, int pos) {
    int keys = tr[idx].keys;
    memmove(tr[idx].pair + pos, tr[idx].pair + pos + 1, sizeof(Pair) * (keys - pos - 1));
    memmove(tr[idx].next + pos, tr[idx].next + pos + 1, sizeof(int) * (keys - pos));
    tr[idx].keys--;
}

// 删除键及其右儿子
inline void del_key_and_right_son(int idx, int pos) {
    int keys = tr[idx].keys;
    memmove(tr[idx].pair + pos, tr[idx].pair + pos + 1, sizeof(Pair) * (keys - pos - 1));
    memmove(tr[idx].next + pos + 1, tr[idx].next + pos + 2, sizeof(int) * (keys - pos - 1));
    tr[idx].keys--;
}

// 将该节点所有子节点父节点设为 f
inline void reset_father(int idx, int f) {
    for (int i = tr[idx].keys; i >= 0; i--)
        fa(tr[idx].next[i]) = f;
}

// 元素索引, 找打元素返回 {true, {key, cnt}}, 否则返回 {false, any}. 时间: O(logn)
pair<bool, Pair> find(int x) {
    if (root == 0)
        return {false, {}};
    int idx = root;
    while (true) {
        pair<int, int> p = find_next(idx, x);
        if (p.first)
            return {x == tr[idx].pair[p.second].key, tr[idx].pair[p.second]};
        idx = p.second;
    }
}

// 插入元素. 时间: O(logn)
void maintain_add(int idx) {
    // case 1: 满足约束, 则不需向上维护插入, 只需向上维护求和
    if (tr[idx].keys <= ULIMIT) {
        maintain(idx);
        return;
    }
    // case 2: 不满足约束且没有父节点, 需要新建父节点, 然后继续 case 3
    if (idx == root) {
        int nxt = cnt_tr++;
        fa(idx) = nxt;
        tr[nxt].next[0] = idx;
        fa(nxt) = 0;
        root = nxt;
    }
    // case 3: 不满足约束, 中位数向父键插入, 左右分裂为两个节点, 作父键左右儿子
    int f = fa(idx), nxt = cnt_tr++, siz = tr[idx].keys, pos = siz / 2;
    add_key_and_right_son(f, find_key(f, tr[idx].pair[0].key), tr[idx].pair[pos], nxt);
    fa(nxt) = f;
    memcpy(tr[nxt].pair, tr[idx].pair + pos + 1, sizeof(Pair) * (siz - pos - 1));
    memcpy(tr[nxt].next, tr[idx].next + pos + 1, sizeof(int) * (siz - pos));
    tr[idx].keys = pos;
    tr[nxt].keys = siz - pos - 1;
    reset_father(nxt, nxt);
    up(idx);
    up(nxt);
    maintain_add(f);
}
void add(int x) {
    // case 1: 空树
    if (root == 0) {
        int nxt = cnt_tr++;
        add_key_and_right_son(nxt, 0, {x, 1}, 0);
        fa(nxt) = 0;
        root = nxt;
        up(root);
        return;
    }
    int idx = root;
    while (true) {
        pair<bool, int> p = find_next(idx, x);
        if (p.first) {
            if (p.second < tr[idx].keys and x == tr[idx].pair[p.second].key) {
                // case 2: 元素已存在
                tr[idx].pair[p.second].cnt++;
                maintain(idx);
            } else {
                // case 3: 元素不存在
                add_key_and_right_son(idx, p.second, {x, 1}, 0);
                maintain_add(idx);
            }
            return;
        }
        idx = p.second;
    }
}

// 删除元素, 元素不存在返回 false. 时间: O(logn)
void maintain_del(int idx) {
    // case 1: 根节点为空, 需删除根节点
    if (idx == root) {
        if (tr[root].keys == 0)
            root = tr[idx].next[0];
        fa(root) = 0;
        up(root);
        return;
    }
    // case 2: 满足约束, 则不需向上维护删除, 只需向上维护求和
    if (tr[idx].keys >= LLIMIT) {
        maintain(idx);
        return;
    }
    int f = fa(idx), w = find_key(f, tr[idx].pair[0].key), siz = tr[idx].keys;
    int lb = w > 0 ? tr[f].next[w - 1] : 0, slb = tr[lb].keys;
    int rb = w < tr[f].keys ? tr[f].next[w + 1] : 0, srb = tr[rb].keys;
    // case 3: 从左或右兄弟移动一节点到当前节点, 左右兄弟依然满足约束
    if (max(slb, srb) > LLIMIT) {
        if (slb > LLIMIT) {
            add_key_and_left_son(idx, 0, tr[f].pair[w - 1], tr[lb].next[slb]);
            tr[f].pair[w - 1] = tr[lb].pair[slb - 1];
            del_key_and_right_son(lb, slb - 1);
            up(lb);
        } else {
            add_key_and_right_son(idx, siz, tr[f].pair[w], tr[rb].next[0]);
            tr[f].pair[w] = tr[rb].pair[0];
            del_key_and_left_son(rb, 0);
            up(rb);
        }
        maintain(idx);
        return;
    }
    // case 4: 左右兄弟均无法借用时, 选择与左或右兄弟将公共父键向下合并, 一定满足约束
    if (lb) {
        add_key_and_right_son(lb, slb, tr[f].pair[w - 1], 0);
        reset_father(idx, lb);
        memcpy(tr[lb].pair + slb + 1, tr[idx].pair, sizeof(Pair) * siz);
        memcpy(tr[lb].next + slb + 1, tr[idx].next, sizeof(int) * (siz + 1));
        tr[lb].keys += siz;
        del_key_and_right_son(f, w - 1);
        up(lb);
    } else {
        add_key_and_right_son(idx, siz, tr[f].pair[w], 0);
        reset_father(rb, idx);
        memcpy(tr[idx].pair + siz + 1, tr[rb].pair, sizeof(Pair) * srb);
        memcpy(tr[idx].next + siz + 1, tr[rb].next, sizeof(int) * (srb + 1));
        tr[idx].keys += srb;
        del_key_and_right_son(f, w);
        up(idx);
    }
    maintain_del(f);  // case 4 变动 father, 因此需要继续向上维护删除
}
bool del(int x) {
    // case 1: 空树
    if (root == 0)
        return false;
    int idx = root;
    while (true) {
        pair<bool, int> p = find_next(idx, x);
        if (p.first) {
            // case 2: 元素不存在
            if (x != tr[idx].pair[p.second].key)
                return false;
            tr[idx].pair[p.second].cnt--;
            // case 3: 无需删除键
            if (tr[idx].pair[p.second].cnt) {
                maintain(idx);
                return true;
            }
            // case 4: 需要删除键
            if (leaf(idx)) {
                // subcase 1: 如为叶子节点, 删除后维护
                del_key_and_left_son(idx, p.second);
            } else {
                // subcase 2: 如非, 与后继交换后删除后继, 后继一定是叶子
                int nxt = tr[idx].next[p.second + 1];
                while (tr[nxt].next[0])
                    nxt = tr[nxt].next[0];
                tr[idx].pair[p.second] = tr[nxt].pair[0];
                del_key_and_left_son(nxt, 0);
                idx = nxt;
            }
            maintain_del(idx);
            return true;
        }
        idx = p.second;
    }
}

// 最小元素, 返回 {true, {最小键, cnt}}}, 空树返回 {false, {}}. 时间: O(logn)
pair<bool, Pair> mini() {
    if (root == 0)
        return {false, {}};
    int idx = root;
    while (not leaf(idx))
        idx = tr[idx].next[0];
    return {true, tr[idx].pair[0]};
}

// 最大元素, 返回 {true, {最大键, cnt}}}, 空树返回 {false, {}}. 时间: O(logn)
pair<bool, Pair> maxi() {
    if (root == 0)
        return {false, {}};
    int idx = root;
    while (not leaf(idx))
        idx = tr[idx].next[tr[idx].keys];
    return {true, tr[idx].pair[tr[idx].keys - 1]};
}

// 元素前驱, 最后一个小于 x 的元素. 特别地, 无前驱返回 {false, {}}. 时间: O(logn)
pair<bool, Pair> pre(int x) {
    if (root == 0)
        return {false, {}};
    int idx = root;
    while (true) {
        pair<bool, int> p = find_next(idx, x);
        if (p.first) {
            if (leaf(idx)) {
                while (idx) {
                    int w = find_key(idx, x);
                    if (w)
                        return {true, tr[idx].pair[w - 1]};
                    idx = fa(idx);
                }
                return {false, {}};
            } else {
                idx = tr[idx].next[p.second];
                while (not leaf(idx))
                    idx = tr[idx].next[tr[idx].keys];
                return {true, tr[idx].pair[tr[idx].keys - 1]};
            }
        }
        idx = p.second;
    }
}
inline pair<bool, Pair> pre_or_equal(int x) { return pre(x + 1); }  // 最后一个小于等于 x 的元素

// 元素后继, 第一个大于等于 x 的元素. 特别地, 无后继返回 {false, {}}. 时间: O(logn)
pair<bool, Pair> nxt_or_equal(int x) {
    if (root == 0)
        return {false, {}};
    int idx = root;
    while (true) {
        pair<bool, int> p = find_next(idx, x);
        if (p.first) {
            while (idx) {
                int w = find_key(idx, x);
                if (w < tr[idx].keys)
                    return {true, tr[idx].pair[w]};
                idx = fa(idx);
            }
            return {false, {}};
        }
        idx = p.second;
    }
}
inline pair<bool, Pair> nxt(int x) { return nxt_or_equal(x + 1); }  // 第一个大于 x 的元素

// 元素 x 排名, x 不存在返回 -1. 1-index, 时间: O(logn)
int rk(int x) {
    if (root == 0)
        return -1;
    int idx = root, cnt = 0;
    while (true) {
        pair<bool, int> p = find_next(idx, x);
        if (p.first) {
            if (x == tr[idx].pair[p.second].key) {
                for (int i = p.second - 1; i >= 0; i--)
                    cnt += tr[idx].pair[i].cnt;
                for (int i = p.second; i >= 0; i--)
                    cnt += tr[tr[idx].next[i]].sum;
                return cnt + 1;
            }
            return -1;
        } else {
            int pos = find_key(idx, x);
            for (int i = pos - 1; i >= 0; i--)
                cnt += tr[idx].pair[i].cnt;
            for (int i = pos - 1; i >= 0; i--)
                cnt += tr[tr[idx].next[i]].sum;
        }
        idx = p.second;
    }
}

// 排名 rk 索引, 总数不足 rk 返回 {false, {}}. 1-index, 时间: O(logn)
pair<bool, Pair> kth(int rk) {
    if (tr[root].sum < rk)
        return {false, {}};
    int idx = root;
    while (true) {
        int i = 0;
        for (; i < tr[idx].keys; i++) {
            if (rk <= tr[tr[idx].next[i]].sum)
                break;
            rk -= tr[tr[idx].next[i]].sum + tr[idx].pair[i].cnt;
            if (rk <= 0)
                return {true, tr[idx].pair[i]};
        }
        idx = tr[idx].next[i];
    }
}

// 建树, 建立平衡树, 0-index. 时间: O(nlogn)
int a[MAX];
void build(int n) {
    for (int i = 0; i < n; i++)
        add(a[i]);
}

// 遍历. 时间: O(n)
Pair walk_list[MAX];
int walk_cnt = 0;
void walk(int idx) {
    if (idx == 0) return;
    for (int i = 0; i < tr[idx].keys; i++) {
        walk(tr[idx].next[i]);
        walk_list[walk_cnt++] = tr[idx].pair[i];
    }
    walk(tr[idx].next[tr[idx].keys]);
}
