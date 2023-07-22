// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

std::map<int, int> mp;
std::map<int, int> mp2;
void demo() {
    mp = std::map<int, int>();                                        // 匿名对象.
    mp = std::map<int, int>{{9, 1}, {6, 0}, {3, 0}, {7, 8}, {1, 6}};  // 初始化: {{1, 6}, {3, 0}, {6, 0}, {7, 8}, {9, 1}}
    mp = mp2;                                                         // 参考 set
    std::map<int, int>::iterator it = mp.begin();                     // 参考 set
    mp.clear();                                                       // 参考 set
    int count = mp.count(2);                                          // 参考 set
    bool flag = mp.empty();                                           // 参考 set
    std::map<int, int>::iterator it = mp.end();                       // 参考 set
    std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> p = mp.equal_range(2);
    // 参考 set
    std::map<int, int>::iterator it = mp.erase(it);                                           // 参考 set
    std::map<int, int>::iterator it = mp.erase(it, ++ ++it);                                  // 参考 set
    unsigned long long siz = mp.erase(2);                                                     // 参考 set
    std::map<int, int>::iterator it = mp.find(2);                                             // 参考 set
    std::pair<std::map<int, int>::iterator, bool> it = mp.insert(std::pair<int, int>(2, 2));  // 参考 set
    std::map<int, int>::iterator it = mp.lower_bound(2);                                      // 参考 set
    unsigned long long siz = mp.size();                                                       // 参考 set
    std::map<int, int>::iterator it = mp.upper_bound(2);                                      // 参考 set
}