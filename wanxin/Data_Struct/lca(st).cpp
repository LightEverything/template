/**
 * @file lca(st).cpp
 * @author lightEvething (wanxinnb@outlook.com)
 * @brief 基于st表的lca
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define quick

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>

const int maxn = 5E5 + 7;
using namespace std;
vector<int> ch[maxn]; // 邻接表
int cnt = 0;
int root = 0, n = 0, s = 0;
int num = 0;
int rmq[(maxn << 1)][31];
int oula[(maxn << 1)];
int first[(maxn << 1)];
int to_ei[(maxn << 1)];

void rmqInit()
{
    for (int i = 1; i <= cnt; i++)
        rmq[i][0] = oula[i];
    int m = log2(cnt);
    for (int j = 1; j <= m; j++)
    {
        int t = cnt - (1 << j) + 1;
        for (int i = 1; i <= t; i++)
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j-1]);
    }
}

int rmqFind(int l, int r)
{
    int m = log2(r -l + 1);
    return min(rmq[l][m], rmq[r - (1 << m) + 1][m]);
}

void dfs(int now, int ffa)
{
    int tmp = ++num;
    oula[++cnt] = tmp;
    to_ei[tmp] = now;
    first[now] = cnt;
    for (auto item : ch[now])
    {
        if (item == ffa) continue;
        dfs(item, now);
        oula[++cnt] = tmp;
    }
}

int lca(int a, int b)
{
    if (first[a] > first[b]) swap(a, b);
    return to_ei[rmqFind(first[a], first[b])];
}

int main(int argc, char** argv)
{
#ifdef quick
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    cin >> n >> s >> root;
    for (int i = 0 ; i < n  -1; i++)
    {
        int tfa, tch;
        cin >> tfa >> tch;
        ch[tfa].push_back(tch);
        ch[tch].push_back(tfa);
    }
    dfs(root, 0);
    rmqInit();

    for (int i = 0 ;i < s; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << lca(l, r) << '\n';
    }

    return 0;
}