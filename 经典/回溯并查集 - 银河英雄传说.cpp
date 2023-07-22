// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

/*
# [NOI2002] 银河英雄传说

## 题目背景

公元 $5801$ 年，地球居民迁至金牛座 $\alpha$ 第二行星，在那里发表银河联邦创立宣言，同年改元为宇宙历元年，并开始向银河系深处拓展。

宇宙历 $799$ 年，银河系的两大军事集团在巴米利恩星域爆发战争。泰山压顶集团派宇宙舰队司令莱因哈特率领十万余艘战舰出征，气吞山河集团点名将杨威利组织麾下三万艘战舰迎敌。

## 题目描述

杨威利擅长排兵布阵，巧妙运用各种战术屡次以少胜多，难免恣生骄气。在这次决战中，他将巴米利恩星域战场划分成 $30000$ 列，每列依次编号为 $1, 2,\ldots ,30000$。之后，他把自己的战舰也依次编号为 $1, 2, \ldots , 30000$，让第 $i$ 号战舰处于第 $i$ 列，形成“一字长蛇阵”，诱敌深入。这是初始阵形。当进犯之敌到达时，杨威利会多次发布合并指令，将大部分战舰集中在某几列上，实施密集攻击。合并指令为 `M i j`，含义为第 $i$ 号战舰所在的整个战舰队列，作为一个整体（头在前尾在后）接至第 $j$ 号战舰所在的战舰队列的尾部。显然战舰队列是由处于同一列的一个或多个战舰组成的。合并指令的执行结果会使队列增大。  

然而，老谋深算的莱因哈特早已在战略上取得了主动。在交战中，他可以通过庞大的情报网络随时监听杨威利的舰队调动指令。

在杨威利发布指令调动舰队的同时，莱因哈特为了及时了解当前杨威利的战舰分布情况，也会发出一些询问指令：`C i j`。该指令意思是，询问电脑，杨威利的第 $i$ 号战舰与第 $j$ 号战舰当前是否在同一列中，如果在同一列中，那么它们之间布置有多少战舰。

作为一个资深的高级程序设计员，你被要求编写程序分析杨威利的指令，以及回答莱因哈特的询问。

## 输入格式

第一行有一个整数 $T$（$1 \le T \le 5 \times 10^5$），表示总共有 $T$ 条指令。

以下有 $T$ 行，每行有一条指令。指令有两种格式：

1. `M i j`：$i$ 和 $j$ 是两个整数（$1 \le i,j \le 30000$），表示指令涉及的战舰编号。该指令是莱因哈特窃听到的杨威利发布的舰队调动指令，并且保证第 $i$ 号战舰与第 $j$ 号战舰不在同一列。

2. `C i j`：$i$ 和 $j$ 是两个整数（$1 \le i,j \le 30000$），表示指令涉及的战舰编号。该指令是莱因哈特发布的询问指令。

## 输出格式

依次对输入的每一条指令进行分析和处理：

- 如果是杨威利发布的舰队调动指令，则表示舰队排列发生了变化，你的程序要注意到这一点，但是不要输出任何信息。
- 如果是莱因哈特发布的询问指令，你的程序要输出一行，仅包含一个整数，表示在同一列上，第 $i$ 号战舰与第 $j$ 号战舰之间布置的战舰数目。如果第 $i$ 号战舰与第 $j$ 号战舰当前不在同一列上，则输出 $-1$。

## 样例 #1

### 样例输入 #1

```
4
M 2 3
C 1 2
M 2 4
C 4 2
```

### 样例输出 #1

```
-1
1
```

## 提示

战舰位置图：表格中阿拉伯数字表示战舰编号

![](https://cdn.luogu.com.cn/upload/pic/53.png)
*/

const int MAX = 100005;

int father[MAX];
int father_nodes[MAX];
int nodes[MAX];

int root(int x) {
    if (father[x] == x) return x;
    int y = root(father[x]);
    nodes[x] += nodes[father[x]] - father_nodes[x];
    father_nodes[x] = nodes[y];
    return father[x] = y;
}

void merge(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
        nodes[y] += nodes[x];
        father_nodes[x] = nodes[y];
        father[x] = y;
    }
}

void solve() {
    iota(father, father + MAX, 0);
    fill(nodes, nodes + MAX, 1);
    fill(father_nodes, father_nodes + MAX, 1);
    int q;
    cin >> q;
    while (q--) {
        string opt;
        cin >> opt;
        if (opt[0] == 'M') {
            int x, y;
            cin >> x >> y;
            merge(x, y);
        } else {
            int x, y;
            cin >> x >> y;
            if (root(x) == root(y)) {
                cout << abs(nodes[x] - nodes[y]) - 1 << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
}