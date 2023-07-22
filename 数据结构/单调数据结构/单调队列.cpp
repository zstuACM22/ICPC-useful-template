// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 单调队列 - 以 滑块最小值 为例. 时间: O(n), 内存: O(n)
// https://www.luogu.com.cn/problem/P1886
const int MAX = 1000005;

int a[MAX];

// 此单调队列自动分配索引
int siz, now_id, m;
int head, tail;
pair<int, int> que[MAX];  // ASC

// 初始化. mm: 滑块长度
void init(int mm) {
    siz = 0, now_id = 0, m = mm;
    head = 0, tail = 0;
}

// 推入. 只有初始化可直接调用
void push(int val) {
    while (head < tail and que[tail - 1].second > val)  // Attention
        tail--;
    que[tail++] = {now_id, val};
    siz++, now_id++;
}

// 弹出
void pop() {
    if (que[head].first <= now_id - siz)
        head++;
    siz--;
}

// 移动 (推入 + 弹出). 滑块移动一位
void move(int val) {
    push(val);
    if (siz > m)
        pop();
}

// 查询
int query() { return que[head].second; }

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init(m);
    for (int i = 1; i < m; i++)
        push(a[i]);
    for (int i = m; i <= n; i++) {
        move(a[i]);
        cout << query() << endl;
    }
}