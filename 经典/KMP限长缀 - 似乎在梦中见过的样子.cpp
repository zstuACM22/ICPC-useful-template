// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
似乎在梦中见过的样子

原题来自：2014 年湖北省队互测 Week2

「Madoka，不要相信 QB！」伴随着 Homura 的失望地喊叫，Madoka 与 QB 签订了契约。

这是 Modoka 的一个噩梦，也同时是上个轮回中所发生的事。

为了使这一次 Madoka 不再与 QB 签订契约，Homura 决定在刚到学校的第一天就解决 QB。

然而，QB 也是有许多替身的（但在第八话中的剧情显示它也有可能是无限重生的），不过，意志坚定的 Homura 是不会放弃的——她决定消灭所有可能是 QB 的东西。

现在，她已感受到附近的状态，并且把它转化为一个长度为 nn 的字符串交给了学 OI 的你。

现在你从她的话中知道，所有形似于 A+B+A 的字串都是 QB 或它的替身，且 |A| \geq k,|B| \geq 1, ∣A∣ ≥ k, ∣B∣ ≥ 1

（位置不同其他性质相同的子串算不同子串，位置相同但拆分不同的子串算同一子串），然后你必须尽快告诉 Homura 这个答案——QB 以及它的替身的数量。

注：对于一个字符串 S，|S| 表示 S 的长度。
*/

const int MAX = 1005;

char s[MAX];
int nxt[MAX];  // 最长公共真前后缀
int pre[MAX];  //  长度>k 的最短公共真前后缀; 若不存在, 保存同 nxt

void solve() {
    int k;
    cin >> s + 1 >> k;
    int n = strlen(s + 1);
    int res = 0;
    nxt[0] = 0, nxt[1] = 0;
    pre[0] = 0, pre[1] = 0;
    for (int m = 0; m < n; m++) {
        char *s = ::s + m;
        // 线性处理最长公共真前后缀
        for (int i = 2, j = 0; i <= n - m; i++) {
            while (j and s[i] != s[j + 1]) j = nxt[j];
            if (s[i] == s[j + 1]) j++;
            nxt[i] = j;
            pre[i] = pre[j] >= k ? pre[j] : j;
            if (k <= pre[i] and pre[i] * 2 < i) res++;  // 根据题意
        }
    }
    cout << res << endl;
}