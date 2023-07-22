// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 字典树. 时间: O(sum(n)q), 内存: O(sum(n))
const int MAXN = 100005;
const int MAXM = 1000005;

struct Trie {
    int cnt = 0;
    map<char, int> next;  // O(log128) 访问, 动态内存
    // int next[128] = {0};  // O(1) 访问, 静态内存
} tr[MAXM];
int cnt_tr = 1;

// 重置字典树
void clear() {
    cnt_tr = 0;
    tr[++cnt_tr] = {};
}

// 插入字符串
void insert(const char *s, int n) {
    int idx = 1;
    tr[idx].cnt++;
    for (int i = 0; i <= n; i++) {
        if (tr[idx].next[s[i]]) {
            idx = tr[idx].next[s[i]];
        } else {
            idx = tr[idx].next[s[i]] = ++cnt_tr;
            tr[idx] = {};
        }
        tr[idx].cnt++;
    }
}

// 计数字符串. 返回: 该字符串的个数
int count(const char *s, int n) {
    int idx = 1;
    for (int i = 0; i <= n; i++)
        if (tr[idx].next[s[i]])
            idx = tr[idx].next[s[i]];
        else
            return 0;
    return tr[idx].cnt;
}

// 删除字符串. 如果存在多个仅减一. 返回: 布尔型-删除成功  // 未验证
bool erase(const char *s, int n) {
    if (not count(s, n))
        return false;
    int idx = 1;
    tr[idx].cnt--;
    for (int i = 0; i <= n; i++) {
        idx = tr[idx].next[s[i]];
        tr[idx].cnt--;
    }
    return true;
}

// 计数前缀. 返回: 该前缀的个数
int match(const char *s, int n) {
    int idx = 1;
    for (int i = 0; i < n; i++)
        if (tr[idx].next[s[i]])
            idx = tr[idx].next[s[i]];
        else
            return 0;
    return tr[idx].cnt;
}