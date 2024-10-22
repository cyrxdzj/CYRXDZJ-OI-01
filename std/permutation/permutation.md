# 形成排列的钢琴曲

![星星的旋律](./card_013_016_normal_compressed.jpg)

## 题目描述

时间限制：1s

空间限制：256MB

司想要创作一曲钢琴曲。具体来说，这首钢琴曲共有 $n$ 个音符，每个音符都可以用一个 $[1,n]$ 范围内的正整数表示，第 $i$ 个音符记为 $a_i$。$a$ 必须构成一个**排列**。

同时，$a$ 要满足 $m$ 条限制条件，第 $i$ 条限制条件记为 $x_i$，$y_i$， 表示 $a_{x_i}<a_{y_i}$。

现在，请你验证，是否有这么一个排列，满足上面的所有限制条件。如果有，请你构造任意一个符合要求的排列。

## 输入数据格式

输入文件为 `permutation.in`。

第一行输入两个正整数 $n$ 和 $m$。

接下来的 $m$ 行，第 $i$ 行输入两个正整数 $x_i$，$y_i$，表示限制条件。

## 输出数据格式

输出文件为 `permutation.out`。

若无解，输出一个 $-1$ 即可。

若有解，则输出 $n$ 个用空格分割的数，第 $i$ 个表示 $a_i$。

## 样例与解释

```input1
9 4
5 7
5 9
8 9
6 3
```

```output1
2 1 8 3 4 5 7 6 9
```

还有一种可能的解：

```
1 2 8 3 4 5 7 6 9
```

因为规则没有限制 $a_1$ 和 $a_2$ 的大小关系。

```input2
8 4
4 3
3 4
4 5
2 6
```

```output2
-1
```

怎么可能同时做到 $a_3<a_4$，$a_4<a_3$？

## 更多样例

样例 #3：请见 `permutation3.in` 和 `permutation3.ans`，该样例符合 Subtask 2 的数据范围。

样例 #4：请见 `permutation4.in` 和 `permutation4.ans`，该样例符合 Subtask 3 的数据范围。

样例 #5：请见 `permutation5.in` 和 `permutation5.ans`，该样例符合 Subtask 5 的数据范围。

## Checker 的编译与使用

为了方便你的调试，出题人准备了 checker。考虑到跨平台兼容性，出题人使用下发源代码而非下发可执行文件的方法来下发它。

请将下发文件中的 `checker.cpp` 和 `testlib.h` 放在同一目录下，使用你喜欢的编译器编译 `checker.cpp`。

编译会生成 `checker.exe`（Windows 平台）或 `checker`（Linux 平台）。运行方法是：

```shell
checker.exe <input-file> <output-file> <answer-file>
```

或：

```bash
./checker <input-file> <output-file> <answer-file>
```

对于 Linux 平台，在必要情况下，可以使用此命令为 `checker` 赋予可执行权限：

```bash
chmod +x checker
```

## 数据范围与提示

长度为 $n$ 的排列是一个由 $n$ 个正整数组成的有序数组，数组中每个数的范围在 $[1,n]$ 间，且每个数恰好出现一次。

| Subtask | 分值 | $n$             | $m$                    | 更多特殊性质                                                 |
| ------- | ---- | --------------- | ---------------------- | ------------------------------------------------------------ |
| 1       | 10   | $1\le n\le10$   | $0\le m\le5$           | 无                                                           |
| 2       | 10   | $1\le n\le10^5$ | $0\le m\le5\times10^4$ | 对于所有 $1\le i\le n,1\le j\le n$，有 $x_i\neq y_j$。对于所有 $1\le i<j\le n$，有 $x_i\neq x_j,y_i\neq y_j$。 |
| 3       | 20   | $1\le n\le10^5$ | $m=n-1$                | 对于所有 $1\le k\le n$，至少存在一个 $1\le i\le n$，有 $x_i=k$ 或 $y_i=k$。$y_i$ 互不相同。至少存在一种解。 |
| 4       | 20   | $1\le n\le10^3$ | $0\le m\le3\times10^3$ | 无                                                           |
| 5       | 40   | $1\le n\le10^5$ | $0\le m\le4\times10^5$ | 无                                                           |

对于所有数据，都有：$1\le n\le10^5$，$0\le m\le4\times10^5$。

## 版权信息

题目：[广州市铁一中学 邓子君](https://www.luogu.com.cn/user/387836)

数据：[广州市铁一中学 邓子君](https://www.luogu.com.cn/user/387836)

题面部分内容的版权持有方为 `SEGA Corporation`，`Colorful Palette Inc.`，`Crypton Media Future Inc.`等公司，仅以非商业目的使用。

在 [CC-BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/legalcode.zh-hans) 协议下共享。