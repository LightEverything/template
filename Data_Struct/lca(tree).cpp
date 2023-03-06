#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 5E5 + 7;
vector<int> e[maxn];
int id[maxn];
int to_id[maxn];
int fa[maxn];
int son[maxn];
int siz[maxn];
int deep[maxn];
int top[maxn];
int cnt = 0;

void dfs1(int now, int f, int dep)
{
    siz[now] = 1;
    fa[now] = f;
    deep[now] = dep;

    for (auto y : e[now])
    {
        if (y == f) continue;
        dfs1(y, now, dep + 1);
        siz[now] += siz[y];
        if (!son[now] || siz[son[now]] < siz[y]) son[now] = y;
    }
}

void dfs2(int now, int f, int topn)
{
    id[now] = ++cnt;
    to_id[cnt] = now;
    top[now] = topn;

    if (!son[now]) return;
    dfs2(son[now], now, topn);

    for (auto y : e[now])
    {
        if (y == son[now] || y == f) continue;
        dfs2(y, now, y);
    }
}

int lca(int x, int y)
{
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    for (int i = 1; i <= n -1; i ++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(s, -1, 1);
    dfs2(s, -1, s);

    for (int i = 1; i <= m; i ++)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u,v) << '\n';
    }
    return 0;
}