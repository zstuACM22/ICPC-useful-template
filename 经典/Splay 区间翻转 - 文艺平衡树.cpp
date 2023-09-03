// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# 【模板】文艺平衡树

## 题目描述

您需要写一种数据结构（可参考题目标题），来维护一个有序数列。  

其中需要提供以下操作：翻转一个区间，例如原有序序列是 $5\ 4\ 3\ 2\ 1$，翻转区间是 $[2,4]$ 的话，结果是 $5\ 2\ 3\ 4\ 1$。

## 输入格式

第一行两个正整数 $n,m$，表示序列长度与操作个数。序列中第 $i$ 项初始为 $i$。  
接下来 $m$ 行，每行两个正整数 $l,r$，表示翻转的区间。

## 输出格式

输出一行 $n$ 个正整数，表示原始序列经过 $m$ 次变换后的结果。

## 样例 #1

### 样例输入 #1

```
5 3
1 3
1 3
1 4
```

### 样例输出 #1

```
4 3 2 1 5
```

## 提示

【数据范围】  
对于 $100\%$ 的数据，$1 \le n, m \leq 100000 $，$1 \le l \le r \le n$。
*/

const int MAX = 100005;

struct Splay {
    int father;
    int next[2];
    int sum;
    bool lazy;
} tr[MAX];  // 1-index
int root = 0;
int cnt_tr = 1;

inline void up(int x) { tr[x].sum = tr[tr[x].next[0]].sum + tr[tr[x].next[1]].sum + 1; }

inline void done(int x) {
    if (tr[x].lazy) {
        int &li = tr[x].next[0];
        int &ri = tr[x].next[1];
        tr[li].lazy ^= true;
        tr[ri].lazy ^= true;
        swap(li, ri);
        tr[x].lazy = false;
    }
}

inline bool who(int x) { return x == tr[tr[x].father].next[1]; }

inline void rotate(int x) {
    bool w = who(x);
    int f = tr[x].father, ff = tr[f].father, s = tr[x].next[not w];
    tr[ff].next[who(f)] = x;
    tr[x].father = ff;
    tr[f].next[w] = s;
    tr[s].father = f;
    tr[x].next[not w] = f;
    tr[f].father = x;
    up(f);
    up(x);
}

inline void splay(int x, int tar) {
    for (int f = tr[x].father; f != tar; f = tr[x].father) {
        if (tr[f].father != tar)
            rotate(who(x) == who(f) ? f : x);
        rotate(x);
    }
    if (tar == 0)
        root = x;
}

typedef int iter;

iter kth(int rk, int tar) {
    int idx = root, cnt = 0;
    while (true) {
        done(idx);
        if (tr[tr[idx].next[0]].sum >= rk) {
            idx = tr[idx].next[0];
        } else {
            rk -= tr[tr[idx].next[0]].sum + 1;
            if (rk <= 0) {
                splay(idx, tar);
                return idx;
            }
            idx = tr[idx].next[1];
        }
    }
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        tr[cnt_tr - 1].next[1] = cnt_tr;
        tr[cnt_tr].father = cnt_tr - 1;
        cnt_tr++;
    }
    for (int i = cnt_tr - 1; i >= 1; i--)
        up(i);
    root = 1;
    cnt_tr = n + 1;
}

vector<int> out;
void walk(int idx) {
    done(idx);
    if (tr[idx].next[0]) walk(tr[idx].next[0]);
    out.push_back(idx - 1);
    if (tr[idx].next[1]) walk(tr[idx].next[1]);
}

void solve() {
    int n, q;
    cin >> n >> q;
    build(n + 2);
    while (q--) {
        int l, r;
        cin >> l >> r;
        kth(l, 0);
        kth(r + 2, root);
        tr[tr[tr[root].next[1]].next[0]].lazy ^= true;
    }
    walk(root);
    for (int i = 1; i <= n; i++)
        cout << out[i] << ' ';
    cout << endl;
}