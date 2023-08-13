// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Beautiful Matrix
/*
题意:
给定一个二维矩阵，判断其中有多少个中心对称正方形，数据范围 2000x2000。
*/
const int MAX = 2005;

// 会 TLE
#define HASH_DOUBLE   // 双哈开关
// #define HASH_NETURAL  // 自然溢出哈希开关
#define HASH_REV      // 逆序开关

#ifdef HASH_NETURAL
#define HASH_CODE uint64_t
#else
#define HASH_CODE int64_t
#endif

const int HX1 = 157, HY1 = 13331, HM1 = 1000000009;
#ifdef HASH_DOUBLE
const int HX2 = 131, HY2 = 10037, HM2 = 999999937;
#endif

HASH_CODE px1[MAX];
HASH_CODE py1[MAX];
HASH_CODE h1[MAX][MAX];
#ifdef HASH_DOUBLE
HASH_CODE px2[MAX];
HASH_CODE py2[MAX];
HASH_CODE h2[MAX][MAX];
#endif
#ifdef HASH_REV
HASH_CODE g1[MAX][MAX];
#ifdef HASH_DOUBLE
HASH_CODE g2[MAX][MAX];
#endif
#endif

#ifdef HASH_NETURAL
#define mm0(x, m) (x)
#define mm1(x, m) (x)
#define mm2(x, m) (x)
#else
#define mm0(x, m) (((x) % (m) + (m)) % (m))  // use for the uncertained x
#define mm1(x, m) (((x) + (m)) % (m))        // use while x must in [-m, inf)
#define mm2(x, m) ((x) % (m))                // use while x must in [0, inf)
#endif


void hash_init(int n) {
    px1[0] = 1, py1[0] = 1;
#ifdef HASH_DOUBLE
    px2[0] = 1, py2[0] = 1;
#endif
    for (int i = 0; i < n; i++) {
        px1[i + 1] = mm2(px1[i] * HX1, HM1);
        py1[i + 1] = mm2(py1[i] * HY1, HM1);
#ifdef HASH_DOUBLE
        px2[i + 1] = mm2(px2[i] * HX2, HM2);
        py2[i + 1] = mm2(py2[i] * HY2, HM2);
#endif
    }
}

void hash_it(const char s[MAX][MAX], int n, int m) {
    for (int i = 0; i <= n; i++) {
        h1[i][0] = 0;
#ifdef HASH_DOUBLE
        h2[i][0] = 0;
#endif
    }
    for (int j = 0; j <= m; j++) {
        h1[0][j] = 0;
#ifdef HASH_DOUBLE
        h2[0][j] = 0;
#endif
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            h1[i + 1][j + 1] = mm0((h1[i][j + 1] * HX1 + h1[i + 1][j] * HY1 + s[i][j] - mm2(h1[i][j] * HX1, HM1) * HY1), HM1);
#ifdef HASH_DOUBLE
            h2[i + 1][j + 1] = mm0((h2[i][j + 1] * HX2 + h2[i + 1][j] * HY2 + s[i][j] - mm2(h2[i][j] * HX2, HM2) * HY2), HM2);
#endif
        }
    }

#ifdef HASH_REV
    for (int i = n + 1; i >= 1; i--) {
        g1[i][m + 1] = 0;
#ifdef HASH_DOUBLE
        g2[i][m + 1] = 0;
#endif
    }
    for (int j = m + 1; j >= 1; j--) {
        g1[n + 1][j] = 0;
#ifdef HASH_DOUBLE
        g2[n + 1][j] = 0;
#endif
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            g1[i + 1][j + 1] = mm0((g1[i + 2][j + 1] * HX1 + g1[i + 1][j + 2] * HY1 + s[i][j] - mm2(g1[i + 2][j + 2] * HX1, HM1) * HY1), HM1);
#ifdef HASH_DOUBLE
            g2[i + 1][j + 1] = mm0((g2[i + 2][j + 1] * HX2 + g2[i + 1][j + 2] * HY2 + s[i][j] - mm2(g2[i + 2][j + 2] * HX2, HM2) * HY2), HM2);
#endif
        }
    }
#endif
}

// 截取子矩阵哈希. 0-index, 左闭右闭
inline int hash_sub(int x, int y, int xx, int yy, bool reverse = false) {
    if (x > xx) swap(x, xx);
    if (y > yy) swap(y, yy);
#ifdef HASH_REV
    if (reverse) {
        x++, y++, xx += 2, yy += 2;
        int s1 = mm0((g1[x][y] - g1[xx][y] * px1[xx - x] - g1[x][yy] * py1[yy - y] + mm2(g1[xx][yy] * px1[xx - x], HM1) * py1[yy - y]), HM1);
#ifdef HASH_DOUBLE
        int s2 = mm0((g2[x][y] - g2[xx][y] * px2[xx - x] - g2[x][yy] * py2[yy - y] + mm2(g2[xx][yy] * px2[xx - x], HM2) * py2[yy - y]), HM2);
        return s1 * HM2 + s2;
#else
        return s1;
#endif
    }
#endif
    xx++, yy++;
    int s1 = mm0((h1[xx][yy] - h1[x][yy] * px1[xx - x] - h1[xx][y] * py1[yy - y] + mm2(h1[x][y] * px1[xx - x], HM1) * py1[yy - y]), HM1);
#ifdef HASH_DOUBLE
    int s2 = mm0((h2[xx][yy] - h2[x][yy] * px2[xx - x] - h2[xx][y] * py2[yy - y] + mm2(h2[x][y] * px2[xx - x], HM2) * py2[yy - y]), HM2);
    return s1 * HM2 + s2;
#else
    return s1;
#endif
}

// 判断是否为回文串. 0-index, 左闭右闭
#ifdef HASH_REV
inline bool is_central_symmetry(int x, int y, int xx, int yy) {
    return hash_sub(x, y, xx, yy) == hash_sub(x, y, xx, yy, true);
}
#endif

// 获取以 (x, y) 为中心的最大中心对称正方形. 0-index, odd: 为奇中心对称矩阵, 否则 (x, y) 表示偶回文子串的左上偏中心
#ifdef HASH_REV
inline int largest_central_symmetry_square(int x, int y, int n, int m, bool odd = true) {
    int l = 0, r = min({x, y, n - 1 - x - (int)(not odd), m - 1 - y - (int)(not odd)});
    while (l <= r) {
        int m = l + r >> 1;
        if (is_central_symmetry(x - m, y - m, x + m + (int)(not odd), y + m + (int)(not odd))) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return r + 1;
}
#endif

char a[MAX][MAX];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    hash_it(a, n, m);
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res += largest_central_symmetry_square(i, j, n, m);
            res += largest_central_symmetry_square(i, j, n, m, false);
        }
    }
    cout << res << endl;
}

int32_t main() {
#ifdef TEST
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
#endif
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    clock_t start_time = clock();
#endif
    cout << fixed << setprecision(2);

    hash_init(MAX - 1);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();

#ifdef LOCAL
    cout << "Used " << call_count << " Function Calls." << endl;
    cout << "Used " << (int)(clock() - start_time) << " Microseconds of Time." << endl;
#endif
    return 0;
}
