#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
// zkw 线段树（区间加法）

int n, n2, m, tr[N << 2], mark[N << 2];
inline int ls(int x) { return x << 1; }
inline int rs(int x) { return x << 1 | 1;}
inline void build() {
    for (int i = 1; i <= n; ++i) {
        cin >> tr[n2 + i - 1];
    }
    for (int i = n2 - 1; i > 0; --i) {
        tr[i] = tr[ls(i)] + tr[rs(i)];
    }
}
inline void add(int x, int k) {
    for (x += n2 - 1; x > 0; x >>= 1) {
        tr[x] += k;
    }
}
inline void add(int l, int r, int k) {
    int cntl = 0, cntr = 0, len = 1;
    for (l += n2 - 2, r += n2; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        tr[l] += cntl * k, tr[r] += cntr * k;
        if (~l & 1) {
            tr[l ^ 1] += len * k;
            mark[l ^ 1] += k;
            cntl += len;
        }
        if (r & 1) {
            tr[r ^ 1] += len * k;
            mark[r ^ 1] += k;
            cntr += len;
        }
    }
    for (; l; l >>= 1, r >>= 1) {
        tr[l] += cntl * k;
        tr[r] += cntr * k;
    }
}
inline int query(int l, int r) {
    int ans = 0, cntl = 0, cntr = 0, len = 1;
    for (l += n2 - 2, r += n2; l ^ r ^ 1; l >>= 1, r >>= 1, len <<= 1) {
        ans += cntl * mark[l] + cntr * mark[r];
        if (~l & 1) ans += tr[l ^ 1], cntl += len;
        if (r & 1) ans += tr[r ^ 1], cntr += len;
    }
    for (; l; l >>= 1, r >>= 1) {
        ans += cntl * mark[l] + cntr * mark[r];
    }
    return ans;
}
inline void out() {
    for (int i = 1; i <= n; ++i) {
        cout << query(i, i) << " ";
    }
    cout << "\n";
}
inline void solve() {
    cin >> n >> m;
    n2 = 1 << ((int)log2(n + 5) + 1);
    build();
    // out();
    for (int i = 1; i <= m; ++i) {
        int p, x, y, k;
        cin >> p;
        if (p == 1) {
            cin >> x >> y >> k;
            add(x, y, k);
            // out();
        }
        else {
            cin >> x >> y;
            cout << query(x, y) << "\n";
        }
    }
}