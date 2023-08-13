// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 单调栈 - 以 最近左较小值 为例. 时间: O(n), 内存: O(n)
// https://www.luogu.com.cn/problem/P5788

// 1-index
const int MAX = 1000005;
int a[MAX];

// 单调栈有时需要正反各一遍
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    stack<pair<int, int>> stk;  // ASC
    stk.push({0, -1});          // Attention: 足够小(如果单增)
    for (int i = 1; i <= n; i++) {
        while (stk.top().second > a[i])  // Attention
            stk.pop();
        cout << stk.top().second << ' ';
        stk.push({i, a[i]});
    }
    cout << endl;
}