// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 超级读写
// @smallC Modified by GreatLiangpi
// #define LOCAL 1  // 调试开关
class IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) ((x) >= '0' and (x) <= '9')
#define isblank(x) ((x) == ' ' or (x) == '\n' or (x) == '\r' or (x) == '\t')

   public:
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
    bool eof = false;

#ifdef LOCAL
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}

    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif

    template <class T>
    friend IO &operator>>(IO &io, T &x) {
        io.read(x);
        return io;
    }

    template <class T>
    friend IO &operator<<(IO &io, const T &x) {
        io.write(x);
        return io;
    }

    inline char gc() {
#ifdef LOCAL  // 调试，可显示字符
        return getchar();
#else
        if (p1 == p2)
            p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
        if (p1 == p2) {
            eof = true;
            return ' ';
        }
        return *p1++;
#endif
    }

    inline void push(const char &c) {
#ifdef LOCAL  // 调试，可显示字符
        putchar(c);
#else
        if (pp - pbuf == MAXSIZE)
            fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
#endif
    }

    template <class T>
    inline bool read(T &x) {
        double tmp = 1;
        bool sign = 0;
        x = 0;
        char ch = gc();
        if (eof)
            return false;
        for (; not isdigit(ch); ch = gc())
            if (ch == '-')
                sign = 1;
        for (; isdigit(ch); ch = gc())
            x = x * 10 + (ch - '0');
        if (ch == '.')
            for (ch = gc(); isdigit(ch); ch = gc())
                tmp /= 10.0, x += tmp * (ch - '0');
        if (sign)
            x = -x;
        return not eof;
    }

    inline bool read(char *s) {
        char ch = gc();
        if (eof)
            return false;
        for (; isblank(ch); ch = gc())
            ;
        for (; not isblank(ch); ch = gc())
            *s++ = ch;
        *s = 0;
        return not eof;
    }

    inline bool read(char &c) {
        c = gc();
        if (eof)
            return false;
        for (; isblank(c); c = gc())
            ;
        return not eof;
    }

    template <class T>
    inline void write(T x) {
        if (x < 0)
            x = -x, push('-');  // 负数输出
        static T sta[35];
        T top = 0;
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
        while (top)
            push(sta[--top] + '0');
    }

    inline void write(const char *s) {
        for (; *s; s++) push(*s);
    }
    inline void write(char *s) { write((const char *)s); }
    inline void write(const char &c) { push(c); }

    template <class T>
    inline void write(T x, const char &lastChar) {
        write(x);
        push(lastChar);
    }
} io;