// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 基础莫队 - 以 区间互异性 为例.
const int MAX = 100005;

int a[MAX];
int siz, l, r, cur;
struct Query {
    int index;
    int left;
    int right;
} qry[MAX];
int buk[MAX];
bool out[MAX];

// 排序函数: 左区号升序-右界升序-左界升序
bool cmp(const Query &x, const Query &y) {
    int xx = x.left / siz, yy = y.left / siz;
    if (xx != yy)
        return xx < yy;
    if (x.right != y.right)
        return x.right < y.right;
    return x.left < y.left;
}

// 添加元素  // Attention
int add(int x) {
    buk[a[x]]++;
    if (buk[a[x]] == 1)
        cur++;
}

// 移除元素  // Attention
int del(int x) {
    buk[a[x]]--;
    if (buk[a[x]] == 0)
        cur--;
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    siz = sqrt(n), l = 0, r = 0, cur = 1, buk[a[0]]++;  // Attention: 别忘了设置初始值
    for (int i = 0; i < q; i++) {
        cin >> qry[i].left >> qry[i].right;
        qry[i].index = i;
        qry[i].left--;
        qry[i].right--;
    }
    sort(qry, qry + q, cmp);
    for (int i = 0; i < q; i++) {
        while (qry[i].left < l)
            add(--l);
        while (qry[i].right > r)
            add(++r);
        while (qry[i].left > l)
            del(l++);
        while (qry[i].right < r)
            del(r--);
        if (cur == r - l + 1)
            out[qry[i].index] = true;
        else
            out[qry[i].index] = false;
    }
    for (int i = 0; i < q; i++)
        if (out[i])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
}