// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 1 的 一阶前缀和: n
// 1 的 二阶前缀和: n * (n + 1) / 2
// 1 的 三阶前缀和: n * (n + 1) * (n + 2) / 6
// 1 的 k 阶前缀和: C(n + k - 1, k)

// n 的 一阶前缀和: n * (n + 1) / 2
// n^2 的 一阶前缀和: n * (n + 1) * (2 * n + 1) / 6
// n^3 的 一阶前缀和: n * n * (n + 1) * (n + 1) / 4

// 常见质数: 998244353, 1000000007, 1000000009
// 质因数个数: logn
// 因数个数: n^(1/2)
// 1e9 互异质因数个数: 9
// 1e9 一般因数个数: 1344

// pi = M_PI = acos(-1)
// e  = M_E  = exp(1)
double log(double x);              // ln x
double log2(double x);             // ln x / ln 2
double log10(double x);            // ln x / ln 10
double hypot(double x, double y);  // sqrt(x * x, y * y)

int32_t atoi(const char *_Str);                                 // char * -> int
int64_t atoll(const char *_Str);                                // char * -> long long
double atof(const char *_Str);                                  // char * -> double
int32_t sscanf(const char *_source, const char *_format, ...);  // similar to scanf but read from _source
int32_t sprintf(char *__stream, const char *__format, ...);     // similar to printf but write to __stream

void fill(vector<int>::iterator _first, vector<int>::iterator _last, int _value);  // set same value _value
void iota(vector<int>::iterator _first, vector<int>::iterator _last, int _value);  // set increasing value started from _value
