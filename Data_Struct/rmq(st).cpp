/**
 * @file rmq(st).cpp
 * @author lightEvething (wanxinnb@outlook.com)
 * @brief rmq的st表版
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 1E5 + 7;
int n, m;
int a[maxn] = {0};
int rmq[maxn][31] = {0};

void rmqInit()
{
    for (int i = 1; i <= n; i++)
        rmq[i][0] = a[i];
    int m = log2(n);
    for (int j = 1; j <= m; j++)
    {
        int t = n - (1 << j) + 1;
        for (int i = 1; i <= t; i++)
            rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j-1]);
    }
}

int rmqFind(int l, int r)
{
    int m = log2(r -l + 1);
    return max(rmq[l][m], rmq[r - (1 << m) + 1][m]);
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
    rmqInit();
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << rmqFind(l, r) << '\n';
    }
    return 0;
}