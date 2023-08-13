// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// spfa - bellman队列优化 O(m) -> O(mn)
const int MAX = 100005;
const int INF = 0x3f3f3f3f3f3f3f3fll;

// 邻接表存图
vector<pair<int, int>> edge[MAX];
int dis[MAX];
bool vis[MAX];
int cou[MAX];

// spfa 单源多点最短路径 正负边 判断负环 队列优化
// 参数: st: 起点, n: 点数. 返回: 是否不存在负环.
// Hack: 网格图 / 菊花图
bool spfa(int st, int n) {
    fill(dis, dis + n + 1, INF);
    fill(vis, vis + n + 1, false);
    fill(cou, cou + n + 1, 0);
    dis[st] = 0;
    vis[st] = true;
    queue<int> que;
    que.push(st);
    while (not que.empty()) {
        int x = que.front();
        que.pop();
        vis[x] = false;
        for (pair<int, int> p : edge[x]) {
            int y = p.first, d = p.second;
            if (dis[y] > dis[x] + d) {
                dis[y] = dis[x] + d;
                cou[y] = cou[x] + 1;
                if (cou[y] >= n)
                    return false;
                if (not vis[y]) {
                    que.push(y);
                    vis[y] = true;
                }
            }
        }
    }
    return true;
}

// Smallest Label First Queue with Tolerance
// Hack: 链套菊花图, 在链上用几个并列在一起的大于容错的小边权边就能欺骗算法多次进入菊花
class SLF : private deque<int> {
   private:
    const int tolerance;

   public:
    SLF(int tolerance = 0) : tolerance(tolerance), deque<int>() {}
    using deque<int>::empty;
    using deque<int>::size;
    using deque<int>::front;
    void push(int x) {
        if (not empty() and dis[front()] > dis[x] + tolerance)
            push_front(x);
        else
            push_back(x);
    }
    void pop() { pop_front(); }
};

// Smallest Label First Queue by Swap
// Hack: 也是外挂诱导链
class SWAP : private deque<int> {
   public:
    SWAP() : deque<int>() {}
    using deque<int>::empty;
    using deque<int>::size;
    using deque<int>::front;
    void push(int x) {
        push_back(x);
        if (front() >= back())
            ::swap(front(), back());
    }
    void pop() {
        pop_front();
        if (not empty() and front() >= back())
            ::swap(front(), back());
    }
};

// Largest Label Last Queue
// Hack: 向起点连一条权值巨大的边
class LLL : private deque<int> {
   private:
    int sum = 0;

   public:
    LLL() : deque<int>() {}
    using deque<int>::empty;
    using deque<int>::size;
    int front() {
        int x = deque<int>::front();
        while (dis[x] * size() > sum) {
            pop_front();
            push_back(x);
            x = deque<int>::front();
        }
        return x;
    }
    void push(int x) {
        push_back(x);
        sum += dis[x];
    }
    void pop() {
        sum -= dis[front()];
        pop_front();
    }
};