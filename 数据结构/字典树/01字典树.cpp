// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 01字典树 - 以 最大异或路径 为例. 时间: O(nlogA), 内存: O(nlogA)
// https://www.luogu.com.cn/problem/P4735
const int MAX = 100005;
const int TRIE_BITS = 32;
struct Trie {
    int cnt = 0;
    int next[2] = {0};
} tr[MAX * TRIE_BITS];
int cnt_tr = 1;

// 数值转二进制表示
bool s[TRIE_BITS];
void to_bin(int x) {
    for (int i = TRIE_BITS - 1; i >= 0; i--) {
        s[i] = x & 1;
        x >>= 1;
    }
}

// 重置字典树
void clear() {
    cnt_tr = 0;
    tr[++cnt_tr] = {0, {0, 0}};
}

// 插入数值
void insert(int x) {
    int idx = 1;
    tr[idx].cnt++;
    to_bin(x);
    for (int i = 0; i < TRIE_BITS; i++) {
        if (tr[idx].next[s[i]]) {
            idx = tr[idx].next[s[i]];
        } else {
            idx = tr[idx].next[s[i]] = ++cnt_tr;
            tr[idx] = {};
        }
        tr[idx].cnt++;
    }
}

// 计数数值. 返回: 该数值的个数
int count(int x) {
    int idx = 1;
    to_bin(x);
    for (int i = 0; i < TRIE_BITS; i++)
        if (tr[idx].next[s[i]]) 
            idx = tr[idx].next[s[i]];
        else
            return 0;
    return tr[idx].cnt;
}

// 删除数值. 如果存在多个仅减一. 返回: 布尔型-删除成功  // 未验证
bool erase(int x) {
    if (not count(x))
        return false;
    int idx = 1;
    tr[idx].cnt--;
    to_bin(x);
    for (int i = 0; i < TRIE_BITS; i++) {
        idx = tr[idx].next[s[i]];
        tr[idx].cnt--;
    }
    return true;
}

// 最大异或和. 返回与 x 的最大异或和
int max_xor(int x) {
    if (tr[1].cnt == 0)
        return -1;
    int idx = 1, y = 0;
    to_bin(x);
    for (int i = 0; i < TRIE_BITS; i++) {
        if (tr[idx].next[!s[i]]) {
            y = y << 1 | !s[i];
            idx = tr[idx].next[!s[i]];
        } else {
            y = y << 1 | s[i];
            idx = tr[idx].next[s[i]];
        }
    }
    return x ^ y;
}