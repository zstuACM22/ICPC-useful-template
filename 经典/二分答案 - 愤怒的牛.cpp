// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 二分答案用于解决最大值最小问题, 有时题目隐含最大值最小条件.

/*
# 进击的奶牛

## 题目描述

Farmer John 建造了一个有 $N$($2$ $\le$ $N$ $\le$ $100000$) 个隔间的牛棚，这些隔间分布在一条直线上，坐标是 $x_1$ ,...,$x_N$
 (0 $\le$ $x_i$ $\le$ $1000000000$)。

他的 $C$($2$ $\le$ $C$ $\le$ $N$) 头牛不满于隔间的位置分布，它们为牛棚里其他的牛的存在而愤怒。为了防止牛之间的互相打斗，Farmer John 想把这些牛安置在指定的隔间，所有牛中相邻两头的最近距离越大越好。那么，这个最大的最近距离是多少呢？

## 输入格式

第 $1$ 行：两个用空格隔开的数字 $N$ 和 $C$。

第 $2$ ~ $N+1$ 行：每行一个整数，表示每个隔间的坐标。

## 输出格式

输出只有一行，即相邻两头牛最大的最近距离。

## 样例 #1

### 样例输入 #1

```
5 3
1
2
8
4
9
```

### 样例输出 #1

```
3
```
*/

const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
int a[MAX];

bool check(int x) {
    int pre = -INF - 1, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] - pre >= x) {
            pre = a[i];
            cnt++;
        }
    }
    return cnt >= m;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int l = 0, r = 1e9;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << r << endl;
}