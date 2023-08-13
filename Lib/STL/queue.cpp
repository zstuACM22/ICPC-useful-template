// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

// 对比 deque
// queue 是一个权限受限的 deque, 裁剪大量方法, 利于便捷使用.
std::queue<int> que;
std::queue<int> que2;
void demo() {
    que = std::queue<int>();              // 参考 deque
    que = que2;                           // 参考 deque
    int &x = que.back();                  // 参考 deque, 该方法事实上不是 queue 应当拥有的.
    bool flag = que.empty();              // 参考 deque
    int &x = que.front();                 // 参考 deque
    que.pop();                            // 参考 deque.pop_front()
    que.push(2);                          // 参考 deque.push_back()
    unsigned long long siz = que.size();  // 参考 deque
}