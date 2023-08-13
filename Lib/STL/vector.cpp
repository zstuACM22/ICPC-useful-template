// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

std::vector<int> vec;
std::vector<int> vec2;
std::set<int> st;
int a[] = {9, 6, 3, 7, 1};
void demo() {
    vec = std::vector<int>();                                              // 匿名对象.
    vec = std::vector<int>(5, 2);                                          // 初始化: {2, 2, 2, 2, 2}
    vec = std::vector<int>{9, 6, 3, 7, 1};                                 // 初始化: {9, 6, 3, 7, 1}
    vec = vec2;                                                            // 拷贝而非引用.
    vec.assign(5, 2);                                                      // 重置: {2, 2, 2, 2, 2}
    vec.assign(std::begin(a), std::end(a));                                // 重置: {9, 6, 3, 7, 1}
    vec.assign(st.begin(), st.end());                                      // 从其他类型拷贝.
    vec.at(0);                                                             // 检测越界的访问.
    int &x = vec.back();                                                   // 返回尾值的引用.
    std::vector<int>::iterator it = vec.begin();                           // 返回头迭代器.
    unsigned long long siz = vec.capacity();                               // 返回容器容量.
    vec.clear();                                                           // 清空容器.
    int *p = vec.data();                                                   // 返回内存指针.
    bool flag = vec.empty();                                               // 返回布尔: 为空.
    std::vector<int>::iterator it = vec.end();                             // 返回尾后迭代器.
    std::vector<int>::iterator it = vec.erase(it);                         // 移除迭代器, 返回下一个迭代器.
    std::vector<int>::iterator it = vec.erase(it, it + 2);                 // 移除区间迭代器, 返回区间的下一个迭代器.
    int &x = vec.front();                                                  // 返回头值的引用.
    std::vector<int>::iterator it = vec.insert(it, 2);                     // 插入数值, 返回插入值的迭代器.
    std::vector<int>::iterator it = vec.insert(it, 5, 2);                  // 插入重复数值, 返回第一个插入值的迭代器.
    std::vector<int>::iterator it = vec.insert(it, st.begin(), st.end());  // 插入区间迭代器, 返回第一个插入值的迭代器. 这里的迭代器可以是任意容器的迭代器.
    vec.pop_back();                                                        // 删除最后一个元素
    vec.push_back(2);                                                      // 追加一个元素
    vec.reserve(100);                                                      // 设置容器容量, 如果容量设置为 < .capacity() 将是无效的.
    vec.resize(100);                                                       // 设置长度, 不足补0, 多余删除.
    vec.shrink_to_fit();                                                   // 缩减容器容量, 使之 == .size().
    unsigned long long siz = vec.size();                                   // 返回容器长度.
}