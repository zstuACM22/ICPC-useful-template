// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Dinic 算法. 时间复杂度: 还要快 -> O(mn^0.5)
const int MAXN = 100005;
const int MAXM = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int n, m, st, ed;
int depth[MAXN];
struct Edge {
    int to;
    int next;
    int val;
} edge[MAXM * 4];  // 一般开四倍内存
int head[MAXN] = {0};
int now_head[MAXN] = {0};
int cnt_edge = 2;
void add(int u, int v, int w) {
    edge[cnt_edge].to = v;
    edge[cnt_edge].val = w;
    edge[cnt_edge].next = head[u];
    head[u] = cnt_edge;
    cnt_edge++;
}

bool bfs() {
    for (int i = 1; i <= n; i++) depth[i] = -1;
    queue<int> que;
    que.push(st);
    depth[st] = 0;
    now_head[st] = head[st];
    while (not que.empty() and depth[ed] == -1) {
        int x = que.front();
        que.pop();
        for (int i = head[x]; i; i = edge[i].next) {
            int y = edge[i].to, w = edge[i].val;
            if (w > 0 and depth[y] == -1) {
                que.push(y);
                depth[y] = depth[x] + 1;
                now_head[y] = head[y];
            }
        }
    }
    return depth[ed] != -1;
}

int dfs(int x, int flow) {
    if (x == ed) return flow;
    int cost = 0;
    for (int i = now_head[x]; i and flow; i = edge[i].next) {
        int y = edge[i].to, w = edge[i].val;
        now_head[x] = i;
        if (w > 0 and depth[y] == depth[x] + 1) {
            int tmp = dfs(y, min(flow, w));
            if (tmp == 0) depth[y] = -1;
            edge[i].val -= tmp;
            edge[i ^ 1].val += tmp;
            cost += tmp;
            flow -= tmp;
        }
    }
    return cost;
}

int dinic() {
    int res = 0;
    for (int i = head[st]; i; i = edge[i].next) {
        res -= edge[i ^ 1].val;
    }
    while (bfs()) {
        dfs(st, INF);
    }
    for (int i = head[st]; i; i = edge[i].next) {
        res += edge[i ^ 1].val;
    }
    return res;
}

void solve() {
    int n1, n2, mm;
    cin >> n1 >> n2 >> mm;
    n = n1 + n2 + 2;
    m = n1 + n2 + mm;
    st = n1 + n2 + 1;
    ed = n1 + n2 + 2;
    for (int i = 1; i <= n1; i++) {
        add(st, i, 1);
        add(i, st, 0);
    }
    for (int i = n1 + 1; i <= n1 + n2; i++) {
        add(i, ed, 1);
        add(ed, i, 0);
    }
    for (int i = 0; i < mm; i++) {
        int u, v;
        cin >> u >> v;
        v += n1;
        add(u, v, 1);
        add(v, u, 0);
    }
    cout << dinic() << endl;
}