// Md
// Module Version 230203
// Powered by GreatLiangpi
#ifdef ONLINE_JUDGE
#define TEST 1  // Test Switch
#else
// #define TEST 1
#define DEBUG 1  // Debug Switch
#endif
#ifndef DEBUG
#define TEST 1
#endif
#include <bits/stdc++.h>
#define int int64_t
#ifdef TEST
#pragma GCC optimize(3, "Ofast", "inline")  // Optimization Switch
#define endl '\n'
#endif
#ifdef DEBUG
#define endl " **\n"
#endif
#define tomax(x, y) x = max(x, (y))
#define tomin(x, y) x = min(x, (y))
using namespace std;
#ifdef TEST
const int MAX = 200005;
#else
#ifdef DEBUG
const int MAX = 105;
#endif
#endif
const int INF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 1000000007;
int call_count = 0;

void solve() {
    ;
}

int32_t main() {
#ifdef TEST
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
#endif
#ifdef DEBUG
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    clock_t start_time = clock();
#endif
    cout << fixed << setprecision(2);

    int t;
    cin >> t;
    while (t--)
        solve();

#ifdef DEBUG
    cout << "Used " << call_count << " Function Calls." << endl;
    cout << "Used " << (int)(clock() - start_time) << " Microseconds of Time." << endl;
#endif
    return 0;
}
