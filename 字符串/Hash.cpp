// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
// #pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 字符串哈希
const int MAX = 1000005;

#define HASH_DOUBLE  // 启用双模数哈希
// #define HASH_NATURE  // 启用自然溢出哈希
// #define HASH_RANDOM  // 启用随机哈希因子
#define HASH_REV     // 启用逆序哈希, 用于回文判定
// #define HASH_JOIN // 启用 hash_join

// 提取 h2
#ifdef HASH_DOUBLE
const int MASK = (1ull << 32) - 1;
#endif

#ifdef HASH_NATURE
#define mm1(x, m) (x)
#define mm2(x, m) (x)
#else
#define mm1(x, m) ((x) % (m))
#define mm2(x, m) (((x) % (m) + (m)) % (m))
#endif

// 哈希因子集. 该数据集最多支持四哈
#ifdef HASH_RANDOM
const int64_t HB_SET[] = {
    131, 157, 293,
    1019, 1471, 1667,
    10037, 13331, 16183,
};
const int64_t HM_SET[] = {998244353, 999999937, 1000000007, 1000000009, 1004535809};
int H1, H2, M1, M2;
#else
const int H1 = 131, H2 = 13331, M1 = 1000000007, M2 = 998244353;
#endif

int h1[MAX], p1[MAX];
#ifdef HASH_DOUBLE
int h2[MAX], p2[MAX];
#endif
#ifdef HASH_REV
int g1[MAX];
#ifdef HASH_DOUBLE
int g2[MAX];
#endif
#endif

#ifdef HASH_JOIN
typedef pair<int, int> HashCode;  // {HashCode, HashLength}
#define hc(x, len) {(x), (len)}
#else
typedef int HashCode;
#define hc(x, len) (x)
#endif

// 自动执行，初始化随机哈希因子，p1, p2 数组初始化
int hash_init = []() {
#ifdef HASH_RANDOM
    srand(time(nullptr));
    int SB = sizeof(HB_SET) / sizeof(HB_SET[0]), SM = sizeof(HM_SET) / sizeof(HM_SET[0]);
    H1 = H2 = HB_SET[rand() % SB];
    while (H1 == H2) H2 = HB_SET[rand() % SB];
    M1 = M2 = HM_SET[rand() % SM];
    while (M1 == M2) M2 = HM_SET[rand() % SM];
#endif
    p1[0] = 1;
#ifdef HASH_DOUBLE
    p2[0] = 1;
#endif
    for (int i = 0; i < MAX; i++) {
        p1[i + 1] = mm1(p1[i] * H1, M1);
#ifdef HASH_DOUBLE
        p2[i + 1] = mm1(p2[i] * H2, M2);
#endif
    }
    return 1;
} ();
// 只对字符串整体哈希，返回 int
inline int hash_code(const char *s, int n) {
    int sum1 = 0;
#ifdef HASH_DOUBLE
    int sum2 = 0;
#endif
    for (int i = 0; i < n; ++i) {
        sum1 = mm1(sum1 * H1 + s[i], M1);
#ifdef HASH_DOUBLE
        sum2 = mm1(sum2 * H2 + s[i], M2);
#endif
    }
#ifdef HASH_DOUBLE
    return sum1 << 32 | sum2;
#else
    return sum1;
#endif
}
// 字符串哈希初始化
inline void hash_it(const char *s, int n) {
    h1[0] = 0;
#ifdef HASH_DOUBLE
    h2[0] = 0;
#endif
    for (int i = 0; i < n; i++) {
        h1[i + 1] = mm1(h1[i] * H1 + s[i], M1);
#ifdef HASH_DOUBLE
        h2[i + 1] = mm1(h2[i] * H2 + s[i], M2);
#endif
    }
#ifdef HASH_REV
    g1[n + 1] = 0;
#ifdef HASH_DOUBLE
    g2[n + 1] = 0;
#endif
    for (int i = n - 1; i >= 0; i--) {
        g1[i + 1] = mm1(g1[i + 2] * H1 + s[i], M1);
#ifdef HASH_DOUBLE
        g2[i + 1] = mm1(g2[i + 2] * H2 + s[i], M2);
#endif
    }
#endif
}
// 截取子串哈希. 0-index, 左闭右闭 (填入值需满足 0 <= l, -1 <= r)
template<bool reverse = false>
inline HashCode hash_sub(int l, int r) {
#ifdef HASH_REV
    if (reverse) {
        int s1 = mm2(g1[l + 1] - g1[r + 2] * p1[r - l + 1], M1);
#ifdef HASH_DOUBLE
        int s2 = mm2(g2[l + 1] - g2[r + 2] * p2[r - l + 1], M2);
        return hc(s1 << 32 | s2, r - l + 1);
#else
        return hc(s1, r - l + 1);
#endif
    }
#endif
    int s1 = mm2(h1[r + 1] - h1[l] * p1[r - l + 1], M1);
#ifdef HASH_DOUBLE
    int s2 = mm2(h2[r + 1] - h2[l] * p2[r - l + 1], M2);
    return hc(s1 << 32 | s2, r - l + 1);
#else
    return hc(s1, r - l + 1);
#endif
}
// 连接子串哈希
#ifdef HASH_JOIN
inline HashCode hash_join(HashCode lhc, HashCode rhc) {
#ifdef HASH_DOUBLE
    int lh1 = lhc.first >> 32, lh2 = lhc.first & MASK, llen = lhc.second;
    int rh1 = rhc.first >> 32, rh2 = rhc.first & MASK, rlen = rhc.second;
#else
    int lh1 = lhc.first, llen = lhc.second;
    int rh1 = rhc.first, rlen = rhc.second;
#endif
    int s1 = mm1(lh1 * p1[rlen] + rh1, M1);
#ifdef HASH_DOUBLE
    int s2 = mm1(lh2 * p2[rlen] + rh2, M2);
    return {s1 << 32 | s2, llen + rlen};
#else
    return {s1, llen + rlen};
#endif
}
#endif
// 判断回文
#ifdef HASH_REV
inline bool is_palindrome(int l, int r) {
    return hash_sub(l, r) == hash_sub<true>(l, r);
}
#endif