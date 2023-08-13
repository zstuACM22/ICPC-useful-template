// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 类 set
template <typename _Key, typename _Compare = less<_Key>>
using pbds_set = __gnu_pbds::tree<
    _Key,
    __gnu_pbds::null_type,
    _Compare,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

pbds_set<int> S;
pbds_set<int> S2;

void demo_for_set() {
    vector<int> vec{9, 6, 3, 7, 1};

    // set 基础支持
    S = pbds_set<int>();                                               // 匿名对象
    S = pbds_set<int>(vec.begin(), vec.end());                         // 初始化: {1, 3, 6, 7, 9}
    S = S2;                                                            // 拷贝而非引用.
    pair<pbds_set<int>::iterator, bool> it7flag = S.insert(2);         // 插入元素
    pbds_set<int>::iterator it = S.find(2);                            // 查找数值, 返回迭代器
    bool flag = S.erase(2);                                            // 移除数值
    pbds_set<int>::iterator it = S.erase(it);                          // 移除迭代器, 返回下一个迭代器
    pbds_set<int>::iterator it = S.begin();                            // 返回首迭代器
    pbds_set<int>::iterator it = S.end();                              // 返回尾迭代器
    pbds_set<int>::iterator it = S.lower_bound(2);                     // 返回第一个大于等于值的迭代器
    pbds_set<int>::iterator it = S.upper_bound(2);                     // 返回第一个大于值的迭代器
    size_t siz = S.size();                                             // 返回大小
    bool flag = S.empty();                                             // 返回为空
    S.clear();                                                         // 清空
    for (pbds_set<int>::iterator it = S.begin(); it != S.end(); it++)  // 遍历
        cout << *it << endl;

    // set 拓展支持
    size_t rank = S.order_of_key(2);                  // 元素在集合中的排名, 元素可以不在集合中 (0-index)
    pbds_set<int>::iterator it = S.find_by_order(2);  // 已知排名的元素迭代器 (0-index)
    S.join(S2);                                       // 合并集合, 集合 2 将被清空
    S.split(2, S2);                                   // 分离集合, 小于等于元素的保留, 集合 2 先清空再赋值转移元素
}

// 类 map
template <typename _Key, typename _Tp, typename _Compare = less<_Key>>
using pbds_map = __gnu_pbds::tree<
    _Key,
    _Tp,
    _Compare,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

pbds_map<int, int> M;
pbds_map<int, int> M2;

void demo_for_map() {
    vector<pair<int, int>> vec{{1, 1}, {0, 1}, {0, 1}, {8, 1}, {6, 1}};

    // map 基础支持
    M = pbds_map<int, int>();                                               // 匿名对象
    M = pbds_map<int, int>(vec.begin(), vec.end());                         // 初始化: {1, 3, 6, 7, 9}
    M = M2;                                                                 // 拷贝而非引用.
    pair<pbds_map<int, int>::iterator, bool> it7flag = M.insert({2, 1});    // 插入元素
    pbds_map<int, int>::iterator it = M.find(2);                            // 查找数值, 返回迭代器
    bool flag = M.erase(2);                                                 // 移除数值
    M.erase(it);                                                            // 移除迭代器, 返回下一个迭代器
    pbds_map<int, int>::iterator it = M.begin();                            // 返回首迭代器
    pbds_map<int, int>::iterator it = M.end();                              // 返回尾迭代器
    pbds_map<int, int>::iterator it = M.lower_bound(2);                     // 返回第一个大于等于值的迭代器
    pbds_map<int, int>::iterator it = M.upper_bound(2);                     // 返回第一个大于值的迭代器
    size_t siz = M.size();                                                  // 返回大小
    bool flag = M.empty();                                                  // 返回为空
    M.clear();                                                              // 清空
    int &x = M[2];                                                          // 索引
    for (pbds_map<int, int>::iterator it = M.begin(); it != M.end(); it++)  // 遍历
        cout << it->first << ' ' << it->second << endl;

    // map 拓展支持
    size_t rank = M.order_of_key(2);                       // 元素在集合中的排名, 元素可以不在集合中 (0-index)
    pbds_map<int, int>::iterator it = M.find_by_order(2);  // 已知排名的元素迭代器 (0-index)
    M.join(M2);                                            // 合并集合, 集合 2 将被清空
    M.split(2, M2);                                        // 分离集合, 小于等于元素的保留, 集合 2 先清空再赋值转移元素
}

// 类 multiset
// pbds 未提供 multiset 需要使用 set + 时间戳 模拟
template <typename _Key, typename _Compare = less<pair<_Key, int>>>
using pbds_mutiset = __gnu_pbds::tree<
    pair<_Key, int>,  // 时间戳
    __gnu_pbds::null_type,
    _Compare,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

// 类 multimap
// pbds 未提供 multimap 需要使用 set + 时间戳 模拟
template <typename _Key, typename _Tp, typename _Compare = less<pair<_Key, int>>>
using pbds_mutimap = __gnu_pbds::tree<
    pair<_Key, int>,  // 时间戳
    _Tp,
    _Compare,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;
