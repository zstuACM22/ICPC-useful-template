// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// AC自动机 (ACA, AhoCorasickAutomaton, 多模式匹配算法).
// 时间: O(An), 内存: O(An) (A 为字符集大小, n 为模式串长度和)
const int MAX = 1000005;

struct ACA {
    int fail;            // 失配状态转移
    vector<int> end;     // 结束状态数量, 如果仅计是否出现, 仅计数即可
    int next[26] = {0};  // 自动机状态转移
} tr[MAX];               // 0-index
int cnt_tr = 0;          // 0 始方便, 因为 fail 默认为 0

#define get_id(c) ((c) - 'a')

// 初始化
void init() {
    for (int i = 0; i <= cnt_tr; i++)
        tr[i] = {};
    cnt_tr = 0;
}

// 向 ACA 动态插入一字符串
void insert(const char *s, int n, int i) {
    int p = 0;
    for (int i = 0; i < n; i++) {
        int &q = tr[p].next[get_id(s[i])];
        if (q == 0)
            q = ++cnt_tr;
        p = q;
    }
    tr[p].end.push_back(i);
}

// 建立 fail 数组, 建立后不可再 insert
void build_fail() {
    queue<int> que;
    for (int i = 0; i < 26; i++)
        if (tr[0].next[i]) {
            tr[tr[0].next[i]].fail = 0;
            que.push(tr[0].next[i]);
        }
    while (que.size()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < 26; i++) {
            int &v = tr[u].next[i], w = tr[tr[u].fail].next[i];
            if (v) {
                tr[v].fail = w;
                que.push(v);
            } else
                v = w;
        }
    }
}

// 计数 ACA 中模式串在 s 中各出现的次数
int res[MAX];
void count_all(const char *s, int n) {
    int p = 0;
    static int cnt[MAX];
    memset(cnt, 0, sizeof(int) * (cnt_tr + 5));
    for (int i = 0; i < n; i++) {
        p = tr[p].next[get_id(s[i])];
        cnt[p]++;
    }
    // 拓扑
    static int in_degree[MAX];
    for (int i = 0; i <= cnt_tr; i++)
        in_degree[tr[i].fail]++;
    queue<int> que;
    for (int i = 0; i <= cnt_tr; i++)
        if (in_degree[i] == 0)
            que.push(i);
    while (que.size()) {
        int x = que.front();
        que.pop();
        int y = tr[x].fail;
        cnt[y] += cnt[x];
        in_degree[y]--;
        if (in_degree[y] == 0)
            que.push(y);
    }
    memset(res, 0, sizeof(int) * (cnt_tr + 5));
    for (int i = 0; i <= cnt_tr; i++)
        for (int idx : tr[i].end)
            res[idx] += cnt[i];
}