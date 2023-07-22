// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// trie 字典树
// 用法与 __gnu_pbds::tree 高度相似
template <typename _Key = string, typename _Tp = __gnu_pbds::null_type>
using pbds_trie = __gnu_pbds::trie<
    _Key,
    _Tp,
    __gnu_pbds::trie_string_access_traits<>,
    __gnu_pbds::pat_trie_tag,
    // __gnu_pbds::trie_prefix_search_node_update>;
    __gnu_pbds::trie_order_statistics_node_update>;

pbds_trie<> tr;
pbds_trie<> tr2;

void solve() {
    vector<string> vec{"10086", "96371", "112345", "114514"};

    // set 基础支持
    tr = pbds_trie<>();                                                // 匿名对象
    tr = pbds_trie<>(vec.begin(), vec.end());                          // 迭代器初始化
    tr = tr2;                                                          // 拷贝而非引用.
    pair<pbds_trie<>::iterator, bool> it7flag = tr.insert("96371");    // 插入元素
    pbds_trie<>::iterator it = tr.find("96371");                       // 查找数值, 返回迭代器
    bool flag = tr.erase("96371");                                     // 移除数值
    pbds_trie<>::iterator it = tr.erase(it);                           // 移除迭代器, 返回下一个迭代器
    pbds_trie<>::iterator it = tr.begin();                             // 返回首迭代器
    pbds_trie<>::iterator it = tr.end();                               // 返回尾迭代器
    pbds_trie<>::iterator it = tr.lower_bound("96371");                // 返回第一个大于等于值的迭代器
    pbds_trie<>::iterator it = tr.upper_bound("96371");                // 返回第一个大于值的迭代器
    size_t siz = tr.size();                                            // 返回大小
    bool flag = tr.empty();                                            // 返回为空
    tr.clear();                                                        // 清空
    for (pbds_trie<>::iterator it = tr.begin(); it != tr.end(); it++)  // 索引
        cout << *it << endl;

    // set 拓展支持
    pair<pbds_trie<>::iterator, pbds_trie<>::iterator> it7jt = tr.prefix_range("11");  // __gnu_pbds::trie_prefix_search_node_update     返回前缀相等迭代器区间
    size_t rank = tr.order_of_key("10086");                                            // __gnu_pbds::trie_order_statistics_node_update  元素在集合中的排名, 元素可以不在集合中 (0-index) 
    pbds_trie<>::iterator it = tr.find_by_order(0);                                    // __gnu_pbds::trie_order_statistics_node_update  已知排名的元素迭代器 (0-index)
    tr.join(tr2);                                                                      // 合并集合, 集合 2 将被清空
    tr.split("112345", tr2);                                                           // 分离集合, 小于等于元素的保留, 集合 2 先清空再赋值转移元素
}
