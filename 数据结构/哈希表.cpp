#include <bits/stdc++.h>
#define ll long long
using namespace std;
// 哈希表

// #define VALUE  // 哈希表第二维开关

#ifdef VALUE
template <int BIT, int SIZE_M, class TYPE>
#else
template <int BIT, int SIZE_M>
#endif
class Hash_Table {
   private:
    static const int SIZE_N = 1 << BIT, MASK = SIZE_N - 1;
    int n, tot;
    int head[SIZE_N];
    int key[SIZE_M], next[SIZE_M];
#ifdef VALUE
    TYPE val[SIZE_M];
#endif
    int Hash_code(int x) {
        return x & MASK;
    }

   public:
    int end() { return 0; }
    // 插入成功返回 true，否则返回 false，实参填入 idx 则不会再次调用 find 函数查找
#ifdef VALUE
    bool insert(const int &x, const int &v, int idx = -1)
#else
    bool insert(const int &x, int idx = -1)
#endif
    {
        int ret = (idx == -1 ? find(x) : idx);
        if (!ret) return false;
        int cur_key = Hash_code(x);
        ++tot;
        key[tot] = x;
        next[tot] = head[cur_key];
        head[cur_key] = tot;
#ifdef VALUE
        val[tot] = v;
#endif
        return true;
    }

    // 找到返回 idx，没找到返回 0
    int find(int x) {
        int cur_key = Hash_code(x);
        for (int i = head[cur_key]; i; i = next[i]) {
            if (key[i] == x) return i;
        }
        return 0;
    }
};
Hash_Table<22, (int)2e5> S;