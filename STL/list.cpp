// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

bool cmp(int x, int y) { return x > y; }
std::list<int> ls;
std::list<int> ls2;
std::set<int> st;
int a[] = {9, 6, 3, 7, 1};
void demo() {
    ls = std::list<int>();                                              // 参考 vector
    ls = std::list<int>(5, 2);                                          // 参考 vector
    ls = std::list<int>{9, 6, 3, 7, 1};                                 // 参考 vector
    ls = ls2;                                                           // 参考 vector
    ls.assign(5, 2);                                                    // 参考 vector
    ls.assign(std::begin(a), std::end(a));                              // 参考 vector
    ls.assign(st.begin(), st.end());                                    // 参考 vector
    int &x = ls.back();                                                 // 参考 vector
    std::list<int>::iterator it = ls.begin();                           // 参考 vector
    ls.clear();                                                         // 参考 vector
    bool flag = ls.empty();                                             // 参考 vector
    std::list<int>::iterator it = ls.end();                             // 参考 vector
    std::list<int>::iterator it = ls.erase(it);                         // 参考 vector
    std::list<int>::iterator it = ls.erase(it, ++ ++it);                // 参考 vector
    int &x = ls.front();                                                // 参考 vector
    std::list<int>::iterator it = ls.insert(it, 2);                     // 参考 vector
    std::list<int>::iterator it = ls.insert(it, 5, 2);                  // 参考 vector
    std::list<int>::iterator it = ls.insert(it, st.begin(), st.end());  // 参考 vector
    ls.merge(ls2);                                                      // 合并序列.
    ls.merge(ls2, cmp);                                                 // 合并排序序列.
    ls.pop_back();                                                      // 移除尾值.
    ls.pop_front();                                                     // 移除头值.
    ls.push_back(2);                                                    // 追加头值.
    ls.push_front(2);                                                   // 追加头值.
    ls.remove(2);                                                       // 移除所有与值相等的元素
    ls.resize(100);                                                     // 设置长度, 不足后补0, 多余删除后部.
    ls.sort();                                                          // 排序序列.
    ls.sort(cmp);                                                       // 自定义排序序列.
    unsigned long long siz = ls.size();                                 // 参考 vector
}