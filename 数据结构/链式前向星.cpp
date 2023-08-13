// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAXN = 10005;
const int MAXM = 1000005;
struct Edge {
    int to;
    int next;
    int val;
} edge[MAXM];
int head[MAXN] = {0};
int cnt_edge = 2;  // Attention: 索引 0/1 禁止被使用
void add(int u, int v, int w) {
    edge[cnt_edge].to = v;
    edge[cnt_edge].val = w;
    edge[cnt_edge].next = head[u];
    head[u] = cnt_edge;
    cnt_edge++;
}

void solve() {
    
}