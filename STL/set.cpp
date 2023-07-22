// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

std::set<int> S;
std::set<int> S2;
void demo() {
    S = std::set<int>();                     // 匿名对象.
    S = std::set<int>{9, 6, 3, 7, 1};        // 初始化: {1, 3, 6, 7, 9}
    S = S2;                                  // 拷贝而非引用.
    std::set<int>::iterator it = S.begin();  // 返回头迭代器.
    S.clear();                               // 清空容器.
    int count = S.count(2);                  // 返回值出现数量.
    bool flag = S.empty();                   // 返回布尔: 为空.
    std::set<int>::iterator it = S.end();    // 返回尾后迭代器.
    std::pair<std::set<int>::iterator, std::set<int>::iterator> p = S.equal_range(2);
    // 返回相等区间指针, 等价于 make_pair(S.lower_bound(2), S.upper_bound(2)).
    std::set<int>::iterator it = S.erase(it);                   // 移除迭代器, 返回下一个迭代器.
    std::set<int>::iterator it = S.erase(it, ++ ++it);          // 移除区间迭代器, 返回区间的下一个迭代器.
    unsigned long long siz = S.erase(2);                        // 移除所有指定值, 返回移除数量.
    std::set<int>::iterator it = S.find(2);                     // 查找数值, 返回值迭代器, 未找到返回尾后迭代器.
    std::pair<std::set<int>::iterator, bool> it = S.insert(2);  // 插入数值, 返回插入值的迭代器.
    std::set<int>::iterator it = S.lower_bound(2);              // 返回第一个大于等于值的迭代器.
    unsigned long long siz = S.size();                          // 返回容器大小.
    std::set<int>::iterator it = S.upper_bound(2);              // 返回第一个大于值的迭代器.
}