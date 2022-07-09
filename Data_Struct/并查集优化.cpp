/**
 * @file 并查集(小优化).cpp
 * @author lightEvething (wanxinnb@outlook.com)
 * @brief 并查集的简单优化版
 * @date 2022-07-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E4 + 7;
int n = 0;
int fa[maxn];
int ranks[maxn]; // 秩

void init()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        ranks[i] = 1;
    }
}

int find(int x)
{
    // 路径压缩
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void merge(int a, int b)
{
    // 秩合并
    int ffa = find(a), ffb = find(b);
    if (ffa == ffb) return ;
    if (ranks[ffa] < ranks[ffb]) swap(ffa, ffb);
    fa[ffb] = ffa;
    ranks[ffa] += ranks[ffb];
}

int main(int argc, char **argv)
{
    int m;
    cin >> n >> m;
    init();
    while (m--)
    {
        int op; // 题目 :操作1是合并，操作2是判断是否在同一个并查集内
        int a, b;
        cin >> op >> a >> b;
        if (op == 1)
            merge(a, b);
        else 
        {
            if (find(a) != find(b))
                cout << "N\n";
            else 
                cout << "Y\n";
        }
    }
    return 0;
}