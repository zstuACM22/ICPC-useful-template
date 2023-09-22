// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

#define MAXSIZE (1ull << 10)
char buf[MAXSIZE], *p1 = nullptr, *p2 = nullptr;
#define isdigit(c) ('0' <= (c) and (c) <= '9')
#define isblank(c) ((c) == ' ' or (c) == '\t' or (c) == '\r' or (c) == '\n')
#ifdef LOCAL
#define gc() getchar()
#else
#define gc() (p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? '\0' : *p1++)
#endif

template <typename T>
inline void read(T &x) {
    x = 0;
    char c = gc();
    bool neg = false;
    while (not isdigit(c)) {
        neg = true;
        c = gc();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    if (neg)
        x = -x;
}

inline void read(char *s) {
    char ch = gc();
    for (; isblank(ch); ch = gc())
        ;
    for (; not isblank(ch); ch = gc())
        *s++ = ch;
    *s = '\0';
}

signed main() {
    int x;
    read(x);
    // cin >> x;
    char s[1024];
    read(s);
    // cin >> s;
    cout << x << ' ' << s << endl;
    return 0;
}