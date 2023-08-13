// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

// 对比 queue
// 事实上 priority_queue 是一个堆, 实时排序的 queue, 两者在方法上基本一致.
template <typename T>
class cmp {
    bool operator()(const T &x, const T &y) { return x < y; }  // 自定义排序函数
};
std::priority_queue<int> heap;                                        // 大顶堆
std::priority_queue<int, std::vector<int>, std::less<int>> heap2;     // 大顶堆
std::priority_queue<int, std::vector<int>, std::greater<int>> heap3;  // 小顶堆
std::priority_queue<int, std::vector<int>, cmp<int>> heap4;           // 自定义排序堆
void demo() {
    heap = std::priority_queue<int>();     // 参考 queue
    heap = heap2;                          // 参考 queue
    bool flag = heap.empty();              // 参考 queue
    heap.pop();                            // 参考 queue
    heap.push(2);                          // 参考 queue
    unsigned long long siz = heap.size();  // 参考 queue
    int x = heap.top();                    // 参考 queue.front(), 注意这里返回值不是一个引用.
}