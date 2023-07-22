// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 类 priority_queue
// 注意 std::priority_queue 与 __gnu_pbds::priority_queue 命名冲突
template <typename _Tp, typename _Sequence = vector<_Tp>, typename _Compare = less<_Tp>>
using pbds_priority_queue = __gnu_pbds::priority_queue<
    _Tp,
    less<_Tp>,
    __gnu_pbds::pairing_heap_tag>;

pbds_priority_queue<int> heap;
pbds_priority_queue<int> heap2;

void solve() {
    pbds_priority_queue<int>::point_iterator it = heap.push(2);  // 压入元素, 返回迭代器. 配对堆 O(1)
    heap.pop();                                                  // 弹出堆顶元素. 配对堆 O(logn) -> O(n)
    int x = heap.top();                                          // 返回堆顶元素. 配对堆 O(1)
    size_t siz = heap.size();                                    // 返回大小
    bool flag = heap.empty();                                    // 返回为空
    heap.modify(it, 3);                                          // 修改迭代器元素. 配对堆 O(logn) -> O(n)
    heap.erase(it);                                              // 移除迭代器元素. 配对堆 O(logn) -> O(n)
    heap.join(heap2);                                            // 合并堆. 配对堆 O(1)
}
