// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 矩阵快速幂. 复杂度: O(log(exponent)), 取模需写入 Matrix类中
// 完整类请见 collection_of_classes::Matrix
// https://www.luogu.com.cn/problem/P3390
class Matrix {
   public:
    vector<vector<int>> data;
    int n, m;
    Matrix() : n(0), m(0) {}
    Matrix(int n, int m) : data(vector<vector<int>>(n, vector<int>(m, 0))), n(n), m(m) {}
    Matrix(vector<vector<int>> vec) : data(vec), n(data.size()), m(data.front().size()) {}
    vector<int> &operator[](int idx) { return data[idx]; }
    Matrix operator*(Matrix &x) {
        if (n != x.m)
            throw "Matrix size error.";
        Matrix res(x.n, m);
        for (int i = 0; i < x.n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < n; k++)
                    res[i][j] = res[i][j] + data[k][j] * x[i][k];
        return res;
    }
    Matrix operator*=(Matrix &x) { return *this = *this * x; }
};

Matrix matrix_pow(Matrix base, int exponent) {
    Matrix res = base;
    exponent--;
    while (exponent) {
        if (exponent & 1)
            res *= base;
        base *= base;
        exponent >>= 1;
    }
    return res;
}