// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# [NOI2007] 社交网络

## 题目描述

在社交网络 ( Social Network ) 的研究中，我们常常使用图论概念去解释一些社会现象。不妨看这样的一个问题:
在一个社交圈子里有 $n$ 个人，人与人之间有不同程度的关系。我们将这个关系网络对应到一个 $n$ 个结点的无向图上，两个不同的人若互相认识，则在他们对应的结点之间连接一条无向边，并附上一个正数权值 $c$ ，$c$ 越小，表示两个人之间的关系越密切。我们可以用对应结点之间的最短路长度来衡量两个人 $s$ 和 $t$ 之间的关系密切程度，注意到最短路径上的其他结点为 $s$ 和 $t$ 的联系提供了某种便利，即这些结点对于 $s$ 和 $t$ 之间的联系有一定的重要程度。我们可以通过统计经过一个结点 $v$ 的最短路径的数目来衡量该结点在社交网络中的重要程度。考虑到两个结点 $A$ 和 $B$ 之间可能会有多条最短路径。我们修改重要程度的定义如下：令 $C_{s,t}$ 表示从s到t的不同的最短路的数目，$C_{s,t}(v)$ 表示经过 $v$ 从 $s$ 到 $t$ 的最短路的数目；则定义：

$$ I(v)=\sum_{s \ne v,t\ne v} \frac{C_{s,t}(v)}{C_{s,t}}$$

为结点 $v$ 在社交网络中的重要程度。为了使 $I(v)$ 和 $C_{s,t}(v)$ 有意义，我们规定需要处理的社交网络都是连通的无向图，即任意两个结点之间都有一条有限长度的最短路径。现在给出这样一幅描述社交网络的加权无向图，请你求出每一个结点的重要程度。

## 输入格式

输入第一行有两个整数 $n$ 和 $m$ ，表示社交网络中结点和无向边的数目。
在无向图中，我们将所有结点从 $1$ 到 $n$ 进行编号。

接下来 $m$ 行，每行用三个整数 $a , b , c$ 描述一条连接结点 $a$ 和 $b$ ，权值为 $c$ 的无向边。
注意任意两个结点之间最多有一条无向边相连，无向图中也不会出现自环（即不存在一条无向边的两个端点是相同的结点）。

## 输出格式

输出包括 $n$ 行，每行一个实数，精确到小数点后 $3$ 位。第 $i$ 行的实数表示结点 $i$ 在社交网络中的重要程度。

## 样例 #1

### 样例输入 #1

```
4 4
1 2 1
2 3 1
3 4 1
4 1 1
```

### 样例输出 #1

```
1.000
1.000
1.000
1.000
```

## 提示

![](https://cdn.luogu.com.cn/upload/pic/1136.png)

对于1号结点而言，只有2号到4号结点和4号到2号结点的最短路经过1号结点，而2号结点和4号结点之间的最短路又有2条。因而根据定义，1号结点的重要程度计算为1/2+1/2=1。由于图的对称性，其他三个结点的重要程度也都是1。

对于 $50\%$ 的数据， $n \le 10 , m \le 45$。
对于 $100\%$ 的数据， $n \le 100 , m \le 4500$ ，任意一条边的权值 $c$ 是正整数且 $1 \leqslant c \leqslant 1000$ 。
所有数据中保证给出的无向图连通，且任意两个结点之间的最短路径数目不超过 $10^{10}$。
*/

const int MAX = 105;
const int INF = 0x3f3f3f3f3f3f3f3fll;

int dis[MAX][MAX];
int dp[MAX][MAX];  // 计数从 u -> v 最短路数量

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                dis[i][j] = 0;
            else
                dis[i][j] = INF;
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = w;
        dis[v][u] = w;
        dp[u][v] = 1;
        dp[v][u] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][k] + dis[k][j] == dis[i][j]) {
                    dp[i][j] += dp[i][k] * dp[k][j];
                } else if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    dp[i][j] = dp[i][k] * dp[k][j];
                }
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        double res = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == k or j == k) continue;
                if (dis[i][k] + dis[k][j] == dis[i][j])
                    res += (double)dp[i][k] * dp[k][j] / dp[i][j];
            }
        }
        cout << res << endl;
    }
}