// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

const int MAX = 100005;

// 绘制类
// 主要用于调试

// 绘制树
// 可以绘制任何树, 但需要书写对于的两个函数
// 函数 DrawTreeNodeInfo(idx) 返回索引 idx 节点的关键信息用于打印
// 函数 DrawTreeAdjacentList(idx) 返回索引 idx 节点的邻接表用于搜索
struct BT {
    int key;
    int next[2];
} tr[MAX];  // 二叉树
#define DrawTreeNodeInfo(idx) ("{" + to_string(idx) + ", " + to_string(tr[idx].key) + "}")
#define DrawTreeAdjacentList(idx) vector<int>(begin(tr[idx].next), end(tr[idx].next))
class DrawTree {
    pair<string, int> p[MAX];
    vector<int> all[MAX];
    int pos[MAX];
    int cnt = 0, max_ = 2, lim = 0;

    int width = 1, cur_draw_link = 0;
    string BLANK, LINE, LEFT_NODE, MID_NODE, RIGHT_NODE;

    void walk(int idx, int level) {
        vector<int> all;
        vector<int> nxt = DrawTreeAdjacentList(idx);

        for (int i = 0; i < nxt.size() / 2; i++)
            if (nxt[i]) {
                all.push_back(nxt[i]);
                walk(nxt[i], level + 1);
            }

        int now = cnt++;
        p[now] = {DrawTreeNodeInfo(idx), level};
        pos[idx] = now;
        max_ = max(max_, (int)p[now].first.size());
        lim = max(lim, level + 1);
        all.push_back(idx);

        for (int i = nxt.size() / 2; i < nxt.size(); i++)
            if (nxt[i]) {
                all.push_back(nxt[i]);
                walk(nxt[i], level + 1);
            }

        this->all[now] = all;
    }

    void do_draw_link(const vector<int> &all) {
        if (all.size() <= 1) return;
        while (cur_draw_link < all.front()) {
            cerr << BLANK << ' ';
            cur_draw_link++;
        }
        cerr << LEFT_NODE << ' ';
        cur_draw_link++;
        for (int i = 1; i < all.size() - 1; i++) {
            while (cur_draw_link < all[i]) {
                cerr << LINE << ' ';
                cur_draw_link++;
            }
            cerr << MID_NODE << ' ';
            cur_draw_link++;
        }
        while (cur_draw_link < all.back()) {
            cerr << LINE << ' ';
            cur_draw_link++;
        }
        cerr << RIGHT_NODE << ' ';
        cur_draw_link++;
    }

    void finish_draw_link() {
        while (cur_draw_link < cnt) {
            cerr << BLANK << ' ';
            cur_draw_link++;
        }
        cur_draw_link = 0;
    }

    string mapLeftRight[MAX];

   public:
    // 设置根节点
    DrawTree(int st) {
        walk(st, 0);
        width = max_;
        for (int i = 0; i < cnt; i++)
            for (int &x : all[i])
                x = pos[x];

        BLANK = string(width, ' ');
        LINE = string(width, '=');
        LEFT_NODE = string(width / 2, ' ') + '*' + string((width - 1) / 2, '=');
        MID_NODE = string(width / 2, '=') + '*' + string((width - 1) / 2, '=');
        RIGHT_NODE = string(width / 2, '=') + '*' + string((width - 1) / 2, ' ');
    }

    // 自上而下绘制, 这样绘制的树相对美观
    void drawTopDown() {
        cerr << setfill('*');
        cerr << setw((width + 1) * cnt) << "" << endl;
        cerr << setfill(' ');
        cerr << setw((width + 1) * cnt) << "Draw Tree" << endl;

        for (int i = 0; i < lim; i++) {
            for (int j = 0; j < cnt; j++)
                if (p[j].second == i)
                    cerr << setw(width) << p[j].first << ' ';
                else
                    cerr << string(width, ' ') << ' ';
            cerr << endl;
            for (int j = 0; j < cnt; j++)
                if (p[j].second == i)
                    do_draw_link(all[j]);
            finish_draw_link();
            cerr << endl;
        }

        cerr << setfill('*');
        cerr << setw((width + 1) * cnt) << "" << endl;
        cerr << setfill(' ');
    }

    // 自左向右绘制, 这样绘制的树相对短小
    void drawLeftRight() {
        int blank = min(max(width / 2 + 1, 4ll), width + 1);

        cerr << setfill('*');
        cerr << setw((lim - 1) * blank + width + 2) << "" << endl;
        cerr << setfill(' ');
        cerr << setw((lim - 1) * blank + width + 2) << "Draw Tree" << endl;

        for (int i = 0; i < cnt; i++)
            mapLeftRight[i] = string((lim - 1) * blank + width + 2, ' ');
        for (int i = 0; i < cnt; i++) {
            const vector<int> &all = this->all[i];
            if (all.size() <= 1) continue;
            for (int j = all.front() + 1; j < all.back(); j++)
                mapLeftRight[j][(p[i].second + 1) * blank] = '|';
            for (int x : all)
                mapLeftRight[x][(p[i].second + 1) * blank] = '*';
        }
        for (int i = 0; i < cnt; i++) {
            memcpy((char *)mapLeftRight[i].c_str() + p[i].second * blank + 1, p[i].first.c_str(), sizeof(char) * p[i].first.size());
            cerr << mapLeftRight[i] << endl;
        }

        cerr << setfill('*');
        cerr << setw((lim - 1) * blank + width + 2) << "" << endl;
        cerr << setfill(' ');
    }
};