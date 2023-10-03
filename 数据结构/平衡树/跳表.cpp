// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 跳表 - Useless
// 跳表并非平衡树但功能相似, 基于链表. 通过多层随机跳跃, 可以实现与平衡树相似的时空复杂度. 
// 相比于平衡树, 其具有代码量小的优势, 但由于必须使用 STL vector 性能一般.
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;
const int MAX_DEPTH = 18;

struct SkipList {
    int key;
    int val;
    vector<int> next;
} nd[MAX];
int cnt;

// 随机数生成器
mt19937 rnd((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r = 0) {
    if (l > r) swap(l, r);
    return rnd() % (r - l + 1) + l;
}

// 初始化
int init() {
    nd[0].key = INF;
    nd[1].next.resize(MAX_DEPTH + 1);
    for (int i = 0; i <= MAX_DEPTH; i++)
        nd[1].next[i] = 0;
    cnt = 2;
    return 0;
};
 
typedef int iter;

// 找到等于 key 的键, 返回索引, 如果存在多个返回最早插入的 (第一个), 找不到返回 -1
iter find(int key) {
    int idx = 1, depth = MAX_DEPTH;
    while (depth >= 0) {
        int nxt = nd[idx].next[depth];
        if (nd[nxt].key >= key)
            depth--;
        else
            idx = nxt;
    }
    int nxt = nd[idx].next[0];
    return nd[nxt].key == key ? nxt : -1;
}

// 插入键值对, 如果键已存在插入已有后面
void add(int key, int val) {
    int idx = 1, depth = MAX_DEPTH;
    int nw = cnt++, d = 0;
    while (d < MAX_DEPTH and (rnd() & 1))
        d++;
    nd[nw].key = key;
    nd[nw].val = val;
    nd[nw].next.resize(d + 1);
    while (depth >= 0) {
        int nxt = nd[idx].next[depth];
        if (nd[nxt].key > key) {
            if (depth <= d) {
                nd[idx].next[depth] = nw;
                nd[nw].next[depth] = nxt;
            }
            depth--;
        } else
            idx = nxt;
    }
}

// 删除一个键, 返回键是否存在, 如果存在多个删除最近插入的 (第一个)
bool del(int key) {
    int idx = 1, nxt, depth = MAX_DEPTH;
    while (depth >= 0) {
        nxt = nd[idx].next[depth];
        if (nd[nxt].key >= key) {
            if (nd[nxt].key == key)
                nd[idx].next[depth] = nd[nxt].next[depth];
            depth--;
        } else
            idx = nxt;
    }
    return nd[nxt].key == key;
}

// 返回最后一个小于 key 的键, 返回索引, 找不到返回 -1
iter pre(int key) {
    int idx = 1, depth = MAX_DEPTH;
    while (depth >= 0) {
        int nxt = nd[idx].next[depth];
        if (nd[nxt].key >= key)
            depth--;
        else
            idx = nxt;
    }
    return idx > 1 ? idx : -1;
}

// 返回第一个大于 key 的键, 返回索引, 找不到返回 -1
iter nxt(int key) {
    int idx = 1, depth = MAX_DEPTH;
    while (depth >= 0) {
        int nxt = nd[idx].next[depth];
        if (nd[nxt].key > key)
            depth--;
        else
            idx = nxt;
    }
    return nd[idx].next[0] > 1 ? nd[idx].next[0] : -1;
}

// 遍历
pair<int, int> walk_list[MAX];
int walk_cnt = 0;
void walk() {
    for (int idx = nd[1].next[0]; idx; idx = nd[idx].next[0])
        walk_list[walk_cnt++] = {nd[idx].key, nd[idx].val};
}