// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 字符串哈希
const int MAX = 1000005;

// 逆序开关: 启用逆序哈希, 包括回文判定
#define HASH_REV

// 哈希因子集. 该数据集最多支持四哈
const int64_t HU_SET[4][3] = {
    {131, 157, 293},
    {1019, 1471, 1667},
    {10037, 13331, 16183},
    {154590409516822759, 2305843009213693951, 4384957924686954497},
};
const int64_t HM_SET[] = {999999937, 1000000007, 1000000009};
int H1 = 131, H2 = 13331, HM = 1000000007;  // 默认哈希因子

int h1[MAX], p1[MAX];
int h2[MAX], p2[MAX];
#ifdef HASH_REV
int g1[MAX];
int g2[MAX];
#endif

struct HashCode {
    int hc1, hc2, len;
    friend bool operator==(const HashCode &x, const HashCode &y) {
        return x.hc1 == y.hc1 and x.hc2 == y.hc2 and x.len == y.len;
    }
    friend bool operator!=(const HashCode &x, const HashCode &y) {
        return not(x == y);
    }
    // friend bool operator<(const HashCode &x, const HashCode &y) {
    //     if (x.len != y.len)
    //         return x.len < y.len;
    //     else if (x.hc1 != y.hc1)
    //         return x.hc1 < y.hc1;
    //     else
    //         return x.hc2 < y.hc2;
    // }
};

// 初始化随机哈希因子
void hash_init(int n) {
    srand(time(nullptr));
    H1 = HU_SET[0][rand() % 3];
    H2 = HU_SET[1][rand() % 3];
    HM = HM_SET[rand() % 3];
    p1[0] = 1, p2[0] = 1;
    for (int i = 0; i < n; i++) {
        p1[i + 1] = (p1[i] * H1) % HM;
        p2[i + 1] = (p2[i] * H2) % HM;
    }
}

// 字符串哈希初始化
void hash_it(const char *s, int n) {
    h1[0] = 0, h2[0] = 0;
    for (int i = 0; i < n; i++) {
        h1[i + 1] = (h1[i] * H1 + s[i]) % HM;
        h2[i + 1] = (h2[i] * H2 + s[i]) % HM;
    }
#ifdef HASH_REV
    g1[n + 1] = 0, g2[n + 1] = 0;
    for (int i = n - 1; i >= 0; i--) {
        g1[i + 1] = (g1[i + 2] * H1 + s[i]) % HM;
        g2[i + 1] = (g2[i + 2] * H2 + s[i]) % HM;
    }
#endif
}

// 截取子串哈希. 0-index, 左闭右闭
HashCode hash_sub(int l, int r, bool reverse = false) {
    if (l > r) swap(l, r);
#ifdef HASH_REV
    if (reverse) {
        int s1 = ((g1[l + 1] - g1[r + 2] * p1[r - l + 1]) % HM + HM) % HM;
        int s2 = ((g2[l + 1] - g2[r + 2] * p2[r - l + 1]) % HM + HM) % HM;
        return {s1, s2, r - l + 1};
    }
#endif
    int s1 = ((h1[r + 1] - h1[l] * p1[r - l + 1]) % HM + HM) % HM;
    int s2 = ((h2[r + 1] - h2[l] * p2[r - l + 1]) % HM + HM) % HM;
    return {s1, s2, r - l + 1};
}

// 连接子串哈希
HashCode hash_join(HashCode lhc, HashCode rhc) {
    int s1 = (lhc.hc1 * p1[rhc.len] + rhc.hc1) % HM;
    int s2 = (lhc.hc2 * p2[rhc.len] + rhc.hc2) % HM;
    return {s1, s2, lhc.len + rhc.len};
}

// 判断回文
#ifdef HASH_REV
bool is_palindrome(int l, int r) {
    return hash_sub(l, r) == hash_sub(l, r, true);
}
#endif

// 哈希表
// 由于字符串哈希呈随机分别，使用哈希表较 map 有极大优化。
template <typename T, int D>
class HashTable {
   private:
    pair<bool, pair<int, T>> data[D];

    int hash(int x) { return x % D; }
    int rehash(int x) { return x + 1; }

   public:
    class iterator {
        pair<int, T> *ptr;

       public:
        iterator(pair<bool, pair<int, T>> data[], int x) : ptr(&data[x].second) {}
        pair<int, T> *operator->() { return ptr; }
        bool operator==(const iterator &oth) { return ptr == oth.ptr; }
    };

    T &operator[](int x) {
        int hash_code = hash(x);
        while (data[hash_code].first and data[hash_code].second.first != x) {
            hash_code = rehash(hash_code);
        }
        return data[hash_code].second.second;
    }

    iterator end() { return iterator(data, D); }

    void insert(const pair<int, T> &p) {
        int hash_code = hash(p.first);
        while (data[hash_code].first)
            hash_code = rehash(hash_code);
        data[hash_code].first = true;
        data[hash_code].second = p;
    }

    iterator find(int x) {
        int hash_code = hash(x);
        while (true) {
            if (not data[hash_code].first)
                return end();
            if (data[hash_code].second.first == x)
                break;
            hash_code = rehash(hash_code);
        }
        return iterator(data, hash_code);
    }
};