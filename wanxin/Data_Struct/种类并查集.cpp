/**
 * @file 种类并查集.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief  种类并查集(多个普通并查集并联)
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 5E4 + 7;
int fa[maxn * 3];

int find(int a)
{
    return fa[a] == a ? a : (fa[a] = find(fa[a]));
}

int main(int argc, char** argv)
{
    int n, m;
    int ans = 0;
    cin >> n >> m;

    for (int i =1; i <= 3 * n; i++)
        fa[i] = i;

    for (int i = 0; i < m; i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        
        if (l > n || r > n || (op == 2 && l == r))
        {
            ans ++;
        }
        else 
        {
            if (op == 1)
            {
                if (find(l) == find(r + n) || find(r) == find(l + n))  ans++;
                else 
                {
                    fa[find(l)] = find(r);
                    fa[find(l + n)] = find(r + n);
                    fa[find(l + 2 * n)] = find(r + 2 * n);
                }
            }
            else 
            {
                if (find(r + n) == find(l) || find(l) == find(r)) ans++;
                else 
                {
                    fa[find(l + n)] = find(r);
                    fa[find(l + 2 * n)] = find(r + n);
                    fa[find(l)] = find(r + 2 * n);
                }
            }
        }
    }

    cout << ans;
    return 0;
}