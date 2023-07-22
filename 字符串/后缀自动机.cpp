// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 后缀自动机(SAM, SuffixAutomaton).
// 时间: O(An), 内存: O(An) (A 为字符集大小, n 为字符最终字符串长度)
const int MAX = 1000005;

struct SAM {
    int father;          // parent tree 中的 father
    int len;             // endpos 等价类中最长串长度, 即等价类中元素个数
    int cnt;             // endpos 等价类中元素在全串中出现次数
    int next[26] = {0};  // 自动机状态转移
} tr[MAX << 1];          // 1-index
int cnt_tr = 1;
int last = 1;

#define get_id(c) ((c) - 'a')

// 初始化 SAM
void init() {
    memset(tr, 0, sizeof(tr));
    cnt_tr = 1;
    last = 1;
}

// 向 SAM 动态追加一个字符
void append(int c) {
    int cur = ++cnt_tr;
    tr[cur].len = tr[last].len + 1;
    tr[cur].cnt = 1;
    int p = last;
    while (p and tr[p].next[c] == 0) {
        tr[p].next[c] = cur;
        p = tr[p].father;
    }
    int q = tr[p].next[c];
    if (q == 0) {
        tr[cur].father = 1;
    } else if (tr[p].len + 1 == tr[q].len) {
        tr[cur].father = q;
    } else {
        int r = ++cnt_tr;
        memcpy(&tr[r], &tr[q], sizeof(SAM));  // 瓶颈
        tr[r].len = tr[p].len + 1;
        tr[r].cnt = 0;
        while (p and tr[p].next[c] == q) {
            tr[p].next[c] = r;
            p = tr[p].father;
        }
        tr[q].father = r;
        tr[cur].father = r;
    }
    last = cur;
}

// 建立 endpos 计数, 建立后不可再 append
void load_tr_cnt(int n) {
    // 桶排序
    static int buk[MAX];
    static int idx[MAX << 1];  // 1-index
    memset(buk, 0, sizeof(buk));
    memset(idx, 0, sizeof(idx));
    for (int i = 1; i <= cnt_tr; i++)
        buk[tr[i].len]++;
    for (int i = 1; i <= n; i++)
        buk[i] += buk[i - 1];
    for (int i = 1; i <= cnt_tr; i++)
        idx[buk[tr[i].len]--] = i;
    for (int i = cnt_tr; i >= 1; i--)
        tr[tr[idx[i]].father].cnt += tr[idx[i]].cnt;
}

// 建 SAM. 时间: O(An) (A 为字符集大小)
void build(const char *s, int n) {
    for (int i = 0; i < n; i++)
        append(get_id(s[i]));
    load_tr_cnt(n);
}

// 字符串出现次数. 时间: O(n)
int count(const char *s, int n) {
    int p = 1;
    for (int i = 0; i < n; i++) {
        p = tr[p].next[get_id(s[i])];
        if (p == 0)
            return 0;
    }
    return tr[p].cnt;
}

// 本质不同子串个数, 不包含空. 时间: O(n)
int count_substring() {
    int res = 0;
    for (int i = 1; i <= cnt_tr; i++) {
        res += tr[i].len - tr[tr[i].father].len;
    }
    return res;
}