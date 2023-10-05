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
#ifdef VALUE
    bool insert(const int &x, const int &v)
#else
    bool insert(const int &x)
#endif
    {
        int ret = find(x);
        if (ret) return false;
        int idx = Hash_code(x);
        ++tot;
        key[tot] = x;
        next[tot] = head[idx];
        head[idx] = tot;
#ifdef VALUE
        val[tot] = v;
#endif
        return true;
    }
    int find(int x) {
        int cur_key = Hash_code(x);
        for (int i = head[cur_key]; i; i = next[i]) {
            if (key[i] == x) return i;
        }
        return 0;
    }
};
Hash_Table<10, 10000> table;