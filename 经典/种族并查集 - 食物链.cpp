// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# [NOI2001] 食物链

## 题目描述

动物王国中有三类动物 $A,B,C$，这三类动物的食物链构成了有趣的环形。$A$ 吃 $B$，$B$ 吃 $C$，$C$ 吃 $A$。

现有 $N$ 个动物，以 $1 \sim N$ 编号。每个动物都是 $A,B,C$ 中的一种，但是我们并不知道它到底是哪一种。

有人用两种说法对这 $N$ 个动物所构成的食物链关系进行描述：

- 第一种说法是 `1 X Y`，表示 $X$ 和 $Y$ 是同类。
- 第二种说法是`2 X Y`，表示 $X$ 吃 $Y$。

此人对 $N$ 个动物，用上述两种说法，一句接一句地说出 $K$ 句话，这 $K$ 句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。

- 当前的话与前面的某些真的话冲突，就是假话；
- 当前的话中 $X$ 或 $Y$ 比 $N$ 大，就是假话；
- 当前的话表示 $X$ 吃 $X$，就是假话。

你的任务是根据给定的 $N$ 和 $K$ 句话，输出假话的总数。

## 输入格式

第一行两个整数，$N,K$，表示有 $N$ 个动物，$K$ 句话。

第二行开始每行一句话（按照题目要求，见样例）

## 输出格式

一行，一个整数，表示假话的总数。

## 样例 #1

### 样例输入 #1

```
100 7
1 101 1
2 1 2
2 2 3
2 3 3
1 1 3
2 3 1
1 5 5
```

### 样例输出 #1

```
3
```

## 提示

对于全部数据，$1\le N\le 5 \times 10^4$，$1\le K \le 10^5$。
*/

const int MAX = 1000005;

int father[MAX * 3];

int root(int x) {
    if (father[x] == x) return x;
    return father[x] = root(father[x]);
}

void merge(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
        father[x] = y;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= 3 * n; i++) {
        father[i] = i;
    }
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        int md, u, v;
        cin >> md >> u >> v;
        if (u > n or v > n) {
            cnt++;
        } else {
            if (md == 1) {
                if (root(u) == root(v + n) or root(u) == root(v + n * 2)) {
                    cnt++;
                } else {
                    merge(u, v);
                    merge(u + n, v + n);
                    merge(u + n * 2, v + n * 2);
                }
            } else {
                if (root(u) == root(v) or root(u) == root(v + n * 2)) {
                    cnt++;
                } else {
                    merge(u, v + n);
                    merge(u + n, v + n * 2);
                    merge(u + n * 2, v);
                }
            }
        }
    }
    cout << cnt << endl;
}