// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

// 对比 deque
// stack 是一个权限受限的 deque, 裁剪大量方法, 利于便捷使用.
std::stack<int> stk;
std::stack<int> stk2;
void demo() {
    stk = std::stack<int>();              // 参考 deque
    stk = stk2;                           // 参考 deque
    bool flag = stk.empty();              // 参考 deque
    stk.pop();                            // 参考 deque.pop_back()
    stk.push(2);                          // 参考 deque.push_back()
    unsigned long long siz = stk.size();  // 参考 deque
    int &x = stk.top();                   // 参考 deque.back()
}