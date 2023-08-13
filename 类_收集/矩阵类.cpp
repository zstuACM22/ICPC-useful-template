// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 矩阵类
class Matrix {
   public:
    vector<vector<int>> data;
    int n, m;
    Matrix() : n(0), m(0) {}
    Matrix(int n, int m) : data(vector<vector<int>>(n, vector<int>(m, 0))), n(n), m(m) {}
    Matrix(vector<vector<int>> vec) : data(vec), n(data.size()), m(data.front().size()) {}
    friend istream &operator>>(istream &cin, Matrix &x) {
        for (vector<int> &vec : x.data)
            for (int &v : vec)
                cin >> v;
        return cin;
    }
    friend ostream &operator<<(ostream &cout, Matrix x) {
        for (vector<vector<int>>::iterator it = x.data.begin(); it != x.data.end(); it++) {
            for (vector<int>::iterator jt = it->begin(); jt != it->end(); jt++)
                cout << *jt << ' ';
            cout << endl;
        }
        return cout;
    }
    vector<int> &operator[](int idx) { return data[idx]; }
    Matrix operator+(Matrix &x) {
        if (n != x.n or m != x.m)
            throw "Matrix size error.";
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = data[i][j] + x[i][j];
        return res;
    }
    Matrix operator-(Matrix &x) {
        if (n != x.n or m != x.m)
            throw "Matrix size error.";
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = data[i][j] - x[i][j];
        return res;
    }
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
    Matrix operator*(int x) {
        Matrix res = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] *= x;
        return res;
    }
    Matrix operator/(int x) {
        Matrix res = *this;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] /= x;
        return res;
    }
    Matrix operator+=(Matrix &x) { return *this = *this + x; }
    Matrix operator-=(Matrix &x) { return *this = *this - x; }
    Matrix operator*=(Matrix &x) { return *this = *this * x; }
    Matrix operator*=(int x) { return *this = *this * x; }
    Matrix operator/=(int x) { return *this = *this / x; }
};