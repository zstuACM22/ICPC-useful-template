// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// Manacher 最长回文子串. 时间: O(n)
const int MAX = 1000005;

char s[MAX << 1 | 1];  // 处理后子串, 0-index
int p[MAX << 1 | 1];   // 最长回文子串长度

// Manacher 算法. s: 文本, n: 文本长度. 返回: 最长回文子串长度.
int manacher(const char *s, int n) {
    int nn = 0;
    for (int i = 0; i < n; i++) {
        ::s[nn++] = '\0';
        ::s[nn++] = s[i];
    }
    ::s[nn++] = '\0';
    s = (const char *)::s;
    n = nn;
    int right_radius = -1, right_center = -1;
    for (int i = 0; i < n; i++) {
        int r = 1;
        // if (s[i] == s[i]) {  // 类 Manacher 可能需要判定本位合法: 如逆反回文
        if (i < right_radius)
            if (p[2 * right_center - i] < right_radius - i)
                r = p[2 * right_center - i];
            else
                r = right_radius - i;
        else
            r = 1;
        while (0 <= i - r and i + r < n)
            if (s[i - r] == s[i + r])  // Attention: 类 Manacher 改此处: 如逆反回文
                r++;
            else
                break;
        // }
        p[i] = r - 1;
        if (i + r > right_radius) {
            right_radius = i + r;
            right_center = i;
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, p[i]);
    return res;
}

// 获取以 i 为中心的最长回文子串长度. 0-index, odd: 为奇回文子串, 否则 i 表示偶回文子串的左偏中心
int longest_palindrome(int i, bool odd = true) {
    return p[i * 2 + 1 + (int)(not odd)];
}

// 判断是否为回文串. 0-index, 左闭右闭
bool is_palindrome(int l, int r) {
    return p[l + r + 1] >= r - l + 1;
}