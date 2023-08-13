// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 多重背包(单调队列优化). 复杂度: O(nm) (跑不过nmlogl)
// https://www.acwing.com/problem/content/submission/6/
const int MAXN = 1000;
const int MAXM = 20000;

int v[MAXN];
int w[MAXN];
int c[MAXN];
int dp[MAXM];

int siz, now_id, mm;
int head, tail;
pair<int, int> que[MAXM];

void init(int x) {
    siz = 0, now_id = 0, mm = x;
    head = 0, tail = 0;
}
void push(int val) {
    while (head < tail and que[tail - 1].second < val)
        tail--;
    que[tail++] = {now_id, val};
    siz++, now_id++;
}
void pop() {
    if (que[head].first < now_id - mm)
        head++;
    siz--;
}
void move(int val) {
    push(val);
    if (siz > mm)
        pop();
}
int query() { return que[head].second; }

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> v[i] >> w[i] >> c[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < v[i]; j++) {
            init(m);
            move(dp[j]);
            for (int k = v[i] + j, cnt = 1; k <= m; k += v[i], cnt++) {
                int x = query();
                move(dp[k] - cnt * w[i]);
                dp[k] = max(dp[k], x + cnt * w[i]);
            }
        }
    cout << dp[m] << endl;
}