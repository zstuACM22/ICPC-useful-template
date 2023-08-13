// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 极角排序
const int MAX = 100005;

const int FLAG[3][3] = {
    {5, 4, 3},
    {6, -1, 2},
    {7, 0, 1},
};

int getf(int x) {
    if (x > 0)
        return 2;
    if (x == 0)
        return 1;
    return 0;
}

class Vec {
   public:
    int x, y, flag;

    Vec(int x = 0, int y = 0) : x(x), y(y), flag(FLAG[getf(x)][getf(y)]) {}

    void set(int x, int y) {
        this->x = x;
        this->y = y;
        this->flag = FLAG[getf(x)][getf(y)];
    }

    // 按从 x 轴正方向逆时针旋转到向量的角度升序, 其次按向量长度升序, 特别地 (0, 0) 被认为是最小的.
    friend bool operator<(const Vec &a, const Vec &b) {
        if (a.flag != b.flag)
            return a.flag < b.flag;
        if (a.y * b.x != a.x * b.y)
            return a.y * b.x < a.x * b.y;
        return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    }
} vec[MAX];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        vec[i].set(x, y);
    }
    sort(vec, vec + n);
    for (int i = 0; i < n; i++) {
        cout << vec[i].x << ' ' << vec[i].y << endl;
    }
}