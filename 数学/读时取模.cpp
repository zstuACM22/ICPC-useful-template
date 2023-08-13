// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAX = 1000005;
const int MOD = 1000000007;

// 读时取模. 返回余数和是否取模.
pair<int, bool> read_mod() {
    static char s[MAX];
    cin >> s;  // Attention: 此处现在使用 cin 读入
    int x = 0;
    bool flag = false;
    for (int i = 0; ; i += 8) {
        // 压位实测约快 3.5 倍
        for (int j = i; j < i + 8; j++) {
            if (s[j] == 0) {
                if (x >= MOD) {
                    x %= MOD;
                    flag = true;
                }
                return {x, flag};
            }
            x = x * 10 + (s[j] - '0');
        }
        if (x >= MOD) {
            x %= MOD;
            flag = true;
        }
    }
}