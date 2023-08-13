// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 模拟堆. 时间: O(qlogn), 内存: O(n)
// 0-index
const int MAX = 100005;

int heap[MAX << 1];  // 堆 (树状数组)
int a2h[MAX << 1];   // 数组索引 -> 堆索引
int h2a[MAX << 1];   // 堆索引 -> 数组索引
int total = 0;       // 总节点 (含已 pop 节点)
int siz = 0;         // 堆大小

// C 风格比较函数
bool cmp(int x, int y) { return x < y; }  // 大顶堆

// 维护映射的交换
void swap_(int u, int v) {
    swap(a2h[h2a[u]], a2h[h2a[v]]);
    swap(h2a[u], a2h[v]);
    swap(heap[u], heap[v]);
    if (u == siz) {
        a2h[h2a[u]] = -1;
        h2a[u] = -1;
    }
    if (v == siz) {
        a2h[h2a[v]] = -1;
        h2a[v] = -1;
    }
}

// 向上维护
void up(int node) {
    while (node and cmp(heap[(node - 1) / 2], heap[node])) {
        swap_(node, (node - 1) / 2);
        node = (node - 1) / 2;
    }
}

// 向下维护
void down(int node) {
    int parent = node;         // 父节点下标
    int child = 2 * node + 1;  // 子节点下标
    while (child < siz) {
        // 判断子节点哪个大, 大的与父节点比较
        if (child + 1 < siz and cmp(heap[child], heap[child + 1]))
            child++;
        if (cmp(heap[parent], heap[child]))  // 判断父节点是否小于子节点
        {
            swap_(parent, child);  // 交换父节点和子节点
            parent = child;        // 子节点下标 赋给 父节点下标
        }
        child = child * 2 + 1;  // 换行, 比较下面的父节点和子节点
    }
}

// 线性初始化堆
void build(int n) {
    total = siz = n;
    for (int i = 0; i < siz; i++) {
        a2h[i] = i;
        h2a[i] = i;
    }
    for (int i = siz / 2 - 1; i >= 0; i--)
        // 必须自下而上
        down(i);
}

// 插入节点
void push(int x) {
    heap[siz] = x;
    a2h[total] = siz;
    h2a[siz] = total;
    up(siz);
    total++;
    siz++;
}

// 返回顶值
int top() { return heap[0]; }

// 删除顶点
int pop() {
    siz--;
    swap_(0, siz);
    down(0);
    return heap[siz];
}

// 修改第 u 个插入的节点
void modify_by_address(int u, int x) {
    int v = a2h[u];
    heap[v] = x;
    down(v);
    up(v);
}

// 删除第 u 个插入的节点. 返回: 布尔型: 节点在堆中
void pop_by_address(int u) {
    int v = a2h[u];
    siz--;
    swap_(v, siz);
    down(v);
    up(v);
}