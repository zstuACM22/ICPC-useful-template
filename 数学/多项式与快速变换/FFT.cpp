// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 快速傅里叶变换(FFT). 时间: O(nlogn)
const int MAX = 100005;
const double PI = acos(-1);

struct Complex {
    double real;
    double img;
    Complex(double real = 0, double img = 0) { this->real = real, this->img = img; }
    Complex operator+(Complex other) { return Complex(real + other.real, img + other.img); }
    Complex operator-(Complex other) { return Complex(real - other.real, img - other.img); }
    Complex operator*(Complex other) { return Complex(real * other.real - img * other.img, real * other.img + img * other.real); }
    Complex operator/(double other) { return Complex(real / other, img / other); }
};

// 快速傅里叶变换. mode: 1: 变换, -1: 逆变换
int tax[MAX << 2];  // 最好开 4 倍内存, 后同, 严格内存: O(2^ceil(log2(n+m-1)))
void _FFT(Complex A[], int lim, int mode) {
    for (int i = 0; i < lim; i++)
        if (i < tax[i])
            swap(A[i], A[tax[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        Complex Wn(cos(PI / mid), mode * sin(PI / mid));
        for (int R = mid << 1, j = 0; j < lim; j += R) {
            Complex w(1, 0);
            for (int k = 0; k < mid; k++, w = w * Wn) {
                Complex x = A[j + k], y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}

// 快速傅里叶卷积. 时间: O((n + m)log(n + m))
// 请保证 res 数组长度 >= n + m - 1
int FFT(int a[], int n, int b[], int m, int res[]) {
    static Complex A[MAX << 2], B[MAX << 2];
    for (int i = 0; i < n; i++)
        A[i] = Complex(a[i]);
    for (int i = 0; i < m; i++)
        B[i] = Complex(b[i]);
    int l = 0, lim = 1;
    while (lim < n + m - 1) {
        lim <<= 1;
        l++;
    }
    for (int i = 0; i < lim; i++)
        tax[i] = (tax[i >> 1] >> 1) | ((i & 1) << (l - 1));
    _FFT(A, lim, 1);
    _FFT(B, lim, 1);
    for (int i = 0; i <= lim; i++)
        A[i] = A[i] * B[i] / lim;
    _FFT(A, lim, -1);
    for (int i = 0; i < n + m - 1; i++)
        res[i] = round(A[i].real);
    return n + m - 1;
}
