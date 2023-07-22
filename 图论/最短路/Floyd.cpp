// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// floyd O(n^3)
const int MAX = 105;

// 邻接矩阵存图
int edge[MAX][MAX];  // 不相连的点为INF, 自身为0

// floyd 多源多点最短路径 正负边
// 参数: n: 点数.
void floyd(int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                edge[i][j] = min(edge[i][j], edge[i][k] + edge[k][j]);
}