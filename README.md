# ICPC-useful-template
浙江理工大学ACM集训队 22 届队员整理的一些ACM-ICPC板子。



## UPD 231007

邦邦咔邦，`smallC233` 加入了队伍，带来了他各种各样的线段树。

新增 `数据结构-跳表`。

`二维数点`、`三维数点` 等模板被陆续加入 `计算几何`。

解决和正在解决一些遗留问题。



## UPD 230922

近期持续新增多种平衡树（在早些时候，位于数据结构）：BST / AVL / Splay / 笛卡尔树 / B 树。

同时新增类_收集-绘制类，方便进行树形结构问题的调试。



## UPD 230813

重构文件结构。

新增多项式相关板子若干。



## UPD 230722

好久不见！`Jamhus_Tao` 重构了他的板子，这次的板子被详细的分属于不同的目录。

同时，`Jamhus_Tao` 新增了他的很多东西。

* `STL` 包含了 `STL`、`pb_ds`、`内建函数优化`。
* `二分` 包含了 `二分`、`三分`、`离散化`。
* `动态规划` ，还有一堆坑要填，过于灵活、板子用不到。
* `图论`，`拓扑排序`、`最短路`、`最小生成树`、`最近公共祖先`、`Tarjan`、`二分图`、`网络流`、`差分约束` 等。
* `字符串`，`KMP`、`Hash`、`Manacher`、`ACA`、`SAM`、`SA` 等。
* `排序`，三个 Useful 的排序，各有长短，`快速排序`、`归并排序`、`基数排序`。
* `搜索`，`广搜`、`迭代加深`、`折半搜索`、`A*`、`IDA*`，冷门 or 板子用不到。
* `数学`，`质数筛法/分解质因数/区间互质/Miller-Robin`、`快速幂/矩阵快速幂`、`排列组合`、`逆元`、`数论分块`、`GCD`、`CRT`、`BSGS`、`FFT`、`定理.md(含博弈论)` 等。
* `数据结构`，`单调栈/单调队列`、`并查集`、`字典树`、`树状数组/线段树`、`ST表`、`分块/莫队`、`堆` 等。
* `计算几何`，`极角排序`、`扫描线`、`凸包`，冷门。
* `类_收集`，`高精度`、`取模类`、`几何类`、`矩阵类`、`超级快读`，各种抽象为类的板子，线上公开赛直接复制粘贴。
* `经典`，收集各种美妙的题型。



## UPD 230111

`Jamhus_Tao` 分支已合并到 `main` 分支。 
`Jamhus_Tao` 分支已移除。 



## UPD 230110

在 `Jamhus_Tao` 分支上传了 `GreatLiangpi` 的板子（已合并到 `main` 分支）。 
板子全部在同一文件 `Function2.0.cpp` 由 `namespace` 分割不同的板子模块。 
**注意：** 板子已发现并未修复的问题：

1. 高精度算法仅支持整数运算，为摘自网络的工程模板，尚未进行效率优化。主要问题包括： 
    * 高精度乘法是朴素的乘法运算，时间复杂度 $O\left(n^2\right)$  （**UPD230722**： $O(max(n,m)^2) \to O(nm)$ ）
    * 高精度除法是高精度与高精度运算，效率极其差（虽然也是平方复杂度）。 （**UPD230722**： $O(max(n,m)^2) \to O(nm)$ ）
    * 不支持高精度与低精度之间的直接运算。
    * `详见 Function2.0.cpp::BigInteger` 

2. 哈希表的实现暂时存在 `BUG` ，哈希表的实现初衷是取代 `std::unordered_map` 而获取优良的时间复杂度，目前在简单测试环境获取了相对于 `std::unordered_map` 的 `50倍` 效率，但是存在未知下标越界问题，欢迎提供修正意见。
    * `详见 Function2.0.cpp::hash::HashMap`

