// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 区间互质计数. 区间 [1, n] 中与 x 互质的数的个数. 复杂度: O(min(n, x)) -> O(2^(min(n, x)^0.5))
vector<int> factor;
int dfs(int level, int count, int value) {
    if (level == factor.size()) {
        return count % 2 ? -value : value;
    } else {
        int res = 0;
        res += dfs(level + 1, count, value);
        res += dfs(level + 1, count + 1, value / factor[level]);
        return res;
    }
}
int interval_coprime(int n, int x) {
    factor.clear();
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            factor.push_back(i);
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        factor.push_back(x);
    int res = dfs(0, 0, n);
    return res;
}