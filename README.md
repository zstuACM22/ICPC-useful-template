# ICPC-useful-template
浙江理工大学ACM集训队22届队员整理的一些ACM-ICPC板子

## UPD 230110
在 `Jamhus_Tao` 分支上传了 `GreatLiangpi` 的板子(已合并到主分支)。  
板子全部在同一文件 `Function2.0.cpp` 由 `namespace` 分割不同的板子模块。  
**注意：** 板子已发现并未修复的问题：
1. 高精度算法仅支持整数运算，为摘自网络的工程模板，尚未进行效率优化。主要问题包括：  
    * 高精度乘法是朴素的乘法运算，时间复杂度 $O\left(n^2\right)$  
    * 高精度除法是高精度与高精度运算，效率及其差（虽然也是平方复杂度）。  
    * 不支持高精度与低精度之间的直接运算。  
    * `详见 Function2.0.cpp::BigInteger`
2. 哈希表的实现暂时存在 `BUG` ，哈希表的实现初中是取代 `std::unordered_map` 而获取优良的时间复杂度，目前在简单测试环境获取了相对于 `std::unordered_map` 的 `50倍` 效率，但是存在未知下标越界问题，欢迎提供修正意见。
    * `详见 Function2.0.cpp::hash::HashMap`

## UPD 230111
`Jamhus_Tao` 分支已合并到 `main` 分支。  
`Jamhus_Tao` 分支已移除。  
