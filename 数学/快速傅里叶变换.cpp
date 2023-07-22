// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 快速傅里叶变换
const int MAX = (1 << 17) * 2 + 5;  // 注意数组开 2^(ceil(log(MAX))) * 2
const double Pi = acos(-1.0);
int tax[MAX];
int limit = 1;
struct Complex {
    double r;
    double i;
    Complex(double r = 0, double i = 0) { this->r = r, this->i = i; }
    Complex operator+(Complex other) { return Complex(r + other.r, i + other.i); }
    Complex operator-(Complex other) { return Complex(r - other.r, i - other.i); }
    Complex operator*(Complex other) { return Complex(r * other.r - i * other.i, r * other.i + i * other.r); }
    Complex operator/(double other) { return Complex(r / other, i / other); }
} a[MAX], b[MAX];

// 快速傅里叶变换. 参数: A: 操作数列, mode: 变换模式: 1: 系数->点集, 2: 点集->系数
void fast_fast_tle(Complex A[], int mode) {
    for (int i = 0; i < limit; i++)
        if (i < tax[i])
            swap(A[i], A[tax[i]]);
    for (int mid = 1; mid < limit; mid <<= 1) {
        Complex Wn(cos(Pi / mid), mode * sin(Pi / mid));
        for (int R = mid << 1, j = 0; j < limit; j += R) {
            Complex w(1, 0);
            for (int k = 0; k < mid; k++, w = w * Wn) {
                Complex x = A[j + k], y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}

// 快速傅里叶卷积. 注意输入与结果为复数数组. 参数: a: 原始数组1 以及 结果数组, n: 原始数组1长度, b: 原始数组2, m: 原始数组2长度. 返回: 结果数组长度
int fast_convolution(Complex a[], int n, Complex b[], int m) {
    // Attention: 将直接在 a, b 数组上修改, 而非拷贝
    int l = 0;
    limit = 1;
    while (limit < n + m - 1) {
        limit <<= 1;
        l++;
    }
    for (int i = 0; i < limit; i++)
        tax[i] = (tax[i >> 1] >> 1) | ((i & 1) << (l - 1));
    fast_fast_tle(a, 1);
    fast_fast_tle(b, 1);
    for (int i = 0; i <= limit; i++)
        a[i] = a[i] * b[i] / limit;
    fast_fast_tle(a, -1);
    return n + m - 1;
}