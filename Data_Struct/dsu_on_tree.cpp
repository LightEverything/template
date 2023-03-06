#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
const int maxn = 1E5 + 7;

vector<int> e[maxn];
int c[maxn];
int fa[maxn], son[maxn];
int siz[maxn], dep[maxn];
int ans[maxn];
int sum = 0, skp = 0;
map<int, int> mp;

void dfs1(int now, int f, int deep)
{
    siz[now] = 1;
    fa[now] = f;
    dep[now] = deep;

    for (auto& y : e[now])
    {
        if (y == f) continue;
        dfs1(y, now, deep + 1);
        siz[now] += siz[y];

        if (!son[now] || siz[son[now]] < siz[y]) 
            son[now] = y;
    }
}

void getdata(int now, int fa)
{
    if (now == skp)
        return ;
    if (mp.count(c[now]) == 0) 
        sum ++;
    mp[c[now]] ++;

    for (auto& y : e[now])
        if (y != fa) getdata(y, now);
}

void dsu(int now, int fa, int del)
{
    for (auto& y : e[now])
    {
        if (y == fa || y == son[now]) 
            continue;
        dsu(y, now, true);
    }

    if (son[now]) dsu(son[now], now, false);

    getdata(now, fa);
    ans[now] = sum;
    if (del)
    {
        sum = 0;
        skp = 0;
        mp.clear();
    }
}

int main(int argc, char** argv)
{
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i ++)
        cin >> c[i];
    for (int i = 1; i <= n - 1; i ++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, -1, 1);

    dsu(1, -1, true);

    for (int i = 1; i <= m; i ++)
    {
        int q;
        cin >> q;
        cout << ans[q] << '\n';
    }
    return 0;
}