// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
7-1 猴子选大王[加强版]
分数 20
作者 李军
单位 陕西理工大学
一群猴子要选大王，遴选的方法是：让M只候选猴子围成一圈，从某位置起顺序编号为0∼M−1号。从第0号开始报N个数字，每轮从0报到N−1，凡报到N−1的猴子即退出候选，接着又从紧邻的下一只猴子开始同样的报数。如此不断循环，最后剩下的一只猴子就选为猴王。问猴王是原来第几号猴子？

输入格式:
在一行中输入两个整数M和N，分别代表猴群数量和报数数。整数与整数之间用空格间隔。

输出格式:
在一行中输出一个数，表示当选猴子编号。

输入样例:
9 2
输出样例:
2
代码长度限制
16 KB
时间限制
40 ms
内存限制
1 MB
*/

// 结论：
void solve() {
    int n, m;
    cin >> n >> m;
    int x = 0;
    for (int i = 1; i <= n; i++) {
        x = (x + m) % i;
    }
    cout << x << endl;
}