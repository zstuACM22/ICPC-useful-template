// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

// 对比 vector
// deque 具有头尾移除与追加的权限, 而 vector 只有尾部追加与移除的权限.
// vector 具有 capacity() 与 reserve() 的方法, deque 中不支持使用.
std::deque<int> deq;
std::deque<int> deq2;
std::set<int> st;
int a[] = {9, 6, 3, 7, 1};
void demo() {
    deq = std::deque<int>();                                              // 参考 vector
    deq = std::deque<int>(5, 2);                                          // 参考 vector
    deq = std::deque<int>{9, 6, 3, 7, 1};                                 // 参考 vector
    deq = deq2;                                                           // 参考 vector
    deq.assign(5, 2);                                                     // 参考 vector
    deq.assign(std::begin(a), std::end(a));                               // 参考 vector
    deq.assign(st.begin(), st.end());                                     // 参考 vector
    deq.at(0);                                                            // 参考 vector
    int &x = deq.back();                                                  // 参考 vector
    std::deque<int>::iterator it = deq.begin();                           // 参考 vector
    deq.clear();                                                          // 参考 vector
    bool flag = deq.empty();                                              // 参考 vector
    std::deque<int>::iterator it = deq.end();                             // 参考 vector
    std::deque<int>::iterator it = deq.erase(it);                         // 参考 vector
    std::deque<int>::iterator it = deq.erase(it, it + 2);                 // 参考 vector
    int &x = deq.front();                                                 // 参考 vector
    std::deque<int>::iterator it = deq.insert(it, 2);                     // 参考 vector
    std::deque<int>::iterator it = deq.insert(it, 5, 2);                  // 参考 vector
    std::deque<int>::iterator it = deq.insert(it, st.begin(), st.end());  // 参考 vector
    deq.pop_back();                                                       // 移除尾值.
    deq.pop_front();                                                      // 移除头值.
    deq.push_back(2);                                                     // 追加头值.
    deq.push_front(2);                                                    // 追加头值.
    deq.resize(100);                                                      // 设置长度, 不足后补0, 多余删除后部.
    deq.shrink_to_fit();                                                  // 参考 vector
    unsigned long long siz = deq.size();                                  // 参考 vector
}