// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 最长严格上升子序列. 时间: O(nlogn)
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int a[MAX];
int low[MAX];
int cnt_low;
int dp[MAX];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    low[0] = 0;
    for (int i = 1; i <= n; i++) {
        low[i] = INF;
    }
    for (int i = 0; i < n; i++) {
        int x = lower_bound(low + 1, low + cnt_low + 1, a[i]) - low;
        dp[i] = x;
        if (x > cnt_low) {
            low[++cnt_low] = a[i];
        } else {
            low[x] = a[i];
        }
    }
}