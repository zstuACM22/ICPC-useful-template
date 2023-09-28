#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = (int)1e6 + 10;
// manacher
// 线性时间求字符串的回文串数量/最长回文串长度/位置
// 时间复杂度 O(n)
// ~ ! 分别是前后哨兵，# 是占位符，注意是否为题目要用的字符

// N 是字符串长度，因为加入了'#'，所以要开两倍空间
int p[N * 2];
char ch[N * 2];
inline int manacher(string &s) {
    int cnt = 0;
    int n = s.size();
    ch[cnt++] = '~';
    for (int i = 0; i < n; ++i) {
        ch[cnt++] = '#';
        ch[cnt++] = s[i];
    }
    ch[cnt++] = '#';
    ch[cnt] = '!';

    int r = 0, mid = 0, ans = 1;
    // int num = 0;
    for (int i = 0; i < cnt; ++i) {
        if (i < r) p[i] = min(p[mid * 2 - i], r - i);
////////// 类 manacher 修改下行的回文串判断条件
        while (ch[i - p[i]] == ch[i + p[i]]) ++p[i];
        --p[i];
        if (i + p[i] > r) { r = i + p[i], mid = i; }  
        if (p[i] > ans) ans = p[i];  // 更新最长回文串，长度是 p[i]，其中心位置是 i
        // num += p[i] / 2;          // 统计回文串数量
    }
    return ans;
}
// 获取原串以 i 为中心的最长回文子串长度, odd: 为奇回文子串, 否则 i 表示偶回文子串的左偏中心
int longest_palindrome(int i, bool is_odd) {
    return p[i * 2 + 2 + !is_odd];
}
// 判断原串的 [l, r] 是否为回文串. 0-index, 左闭右闭
bool is_palindrome(int l, int r) {
    return p[l + r + 2] >= r - l + 1;
}