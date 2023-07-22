// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")

std::string str;
std::string str2;
std::set<char> st;
char a[] = "96371";
void demo() {
    str = std::string();                                              // 匿名对象.
    str = std::string(5, 'a');                                        // 初始化: aaaaa
    str = std::string("123");                                         // 初始化: 123
    str = str2;                                                       // 拷贝而非引用.
    str.append(str2);                                                 // 追加, 等价于 str += str2.
    str.assign(5, 'a');                                               // 重置: aaaaa
    str.assign(std::begin(a), std::end(a));                           // 重置: 96371
    str.assign(st.begin(), st.end());                                 // 从其他类型拷贝.
    str.at(0);                                                        // 检测越界的访问.
    char &x = str.back();                                             // 返回尾值的引用.
    std::string::iterator it = str.begin();                           // 返回头迭代器.
    const char *p = str.c_str();                                      // 返回内存指针.
    unsigned long long siz = str.capacity();                          // 返回容器容量.
    str.clear();                                                      // 清空容器.
    str.compare("123");                                               // 与 C 风格字符串比较, 等价于 strcmp(str.c_str(), "123").
    bool flag = str.empty();                                          // 返回布尔: 为空.
    std::string::iterator it = str.end();                             // 返回尾后迭代器.
    std::string::iterator it = str.erase(it);                         // 移除迭代器, 返回下一个迭代器.
    std::string::iterator it = str.erase(it, it + 2);                 // 移除区间迭代器, 返回区间的下一个迭代器.
    char &x = str.front();                                            // 返回头值的引用.
    int idx = str.find('2');                                          // 返回找到索引, 未找到返回 -1ull.
    int idx = str.find("123");                                        // 返回找到子串索引, 未找到返回 -1ull, 线性时间.
    int idx = str.find_first_not_of('2');                             // 返回首个非匹配索引, 未找到返回 -1ull.
    int idx = str.find_first_not_of("123");                           // 返回首个非匹配串中所有字符的索引, 未找到返回 -1ull.
    int idx = str.find_first_of('2');                                 // 返回首个匹配索引, 等价于 .find('2'), 未找到返回 -1ull.
    int idx = str.find_first_of("123");                               // 返回首个匹配串中任意字符的索引, 未找到返回 -1ull.
    int idx = str.find_last_not_of('2');                              // 返回末个非匹配索引, 未找到返回 -1ull.
    int idx = str.find_last_not_of("123");                            // 返回末个非匹配串中所有字符的索引, 未找到返回 -1ull.
    int idx = str.find_last_of('2');                                  // 返回末个匹配索引, 未找到返回 -1ull.
    int idx = str.find_last_of("123");                                // 返回末个匹配串中任意字符的索引, 未找到返回 -1ull.
    std::string::iterator it = str.insert(it, 2);                     // 插入数值, 返回插入值的迭代器.
    std::string::iterator it = str.insert(it, 5, 2);                  // 插入重复数值, 返回第一个插入值的迭代器.
    std::string::iterator it = str.insert(it, st.begin(), st.end());  // 插入区间迭代器, 返回第一个插入值的迭代器. 这里的迭代器可以是任意容器的迭代器.
    str.pop_back();                                                   // 删除最后一个元素.
    str.push_back(2);                                                 // 追加一个元素.
    str.reserve(100);                                                 // 设置容器容量, 如果容量设置为 < .capacity() 将是无效的.
    str.resize(100);                                                  // 设置长度, 不足补0, 多余删除.
    str.shrink_to_fit();                                              // 缩减容器容量, 使之 == .size().
    unsigned long long siz = str.size();                              // 返回容器长度.
    std::string substr = str.substr(1, 2);                            // 返回索引 1 始, 长度 2 的子串.
}