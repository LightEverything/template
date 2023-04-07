/**
 * @file 树链剖分.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief 树链剖分 + 线段树
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;
const long long maxn = 100000 + 7;
vector<long long > e[maxn << 1];
long long fa[maxn];
long long deep[maxn];
long long siz[maxn];
long long top[maxn];
long long son[maxn];
long long tree[maxn << 2];
long long cnt = 0;
long long to_id[maxn];
long long w[maxn];
long long old[maxn];
long long lazy[maxn << 2];
long long n, m;

void dfs(long long now, long long f)
{
    deep[now] = deep[f] + 1;
    siz[now] = 1;
    fa[now] = f;

    for (auto& y : e[now])
    {
        if (y == f) continue;
        fa[y] = now;
        dfs(y, now);
        siz[now] += siz[y];
        if (!son[now] || siz[son[now]] < siz[y])   son[now] = y;
    }
}


void dfs2(long long now, long long topn)
{
    to_id[now] = ++ cnt;
    w[cnt] = old[now];
    top[now] = topn;
    if (!son[now]) return ;
    dfs2(son[now], topn);

    for (auto& y : e[now])
    {
        if (y == fa[now]) continue;
        if (y != son[now]) 
            dfs2(y, y);
    }
}

long long lca(long long a, long long b)
{
    while (top[a] != top[b])
    {
        if (deep[top[a]] < deep[top[b]]) swap(a, b);
        a = fa[top[a]];
    }
    return deep[a] < deep[b] ? a : b;
}

void build(long long now, long long l, long long r)
{
    if (l == r)
    {
        tree[now] = w[l];
        return ;
    }
    long long mid = (l + r) / 2;
    build(now * 2, l, mid);
    build(now * 2 + 1, mid + 1, r);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

void update(long long now, long long l, long long r)
{
    lazy[now * 2] += lazy[now], lazy[now * 2 + 1] += lazy[now];
    long long mid = (l + r) / 2;
    tree[now * 2] += lazy[now] * (mid - l + 1), tree[now * 2 + 1] += lazy[now] * (r - mid);
    lazy[now] = 0;
}

void change(long long now, long long l, long long r, long long nl, long long nr, long long num)
{
    if (nl<= l && nr >= r)
    {
        lazy[now] += num;
        tree[now] += (r - l + 1) * num;
        return ;
    }
    if (lazy[now])
        update(now, l, r);
    long long mid = (l + r) / 2;
    if (nl <= mid) change(now * 2, l, mid, nl, nr, num);
    if (nr >= mid + 1) change(now * 2 + 1, mid + 1, r, nl, nr, num);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

long long ask(long long now, long long l, long long r, long long nl, long long nr)
{
    if (nl <= l && nr >= r)
    {
        return tree[now];
    }
    long long ans = 0;
    if (lazy[now])
        update(now, l, r);
    long long mid = (l + r) / 2;
    if (nl <= mid) ans += ask(now * 2, l ,mid, nl, nr);
    if (nr >= mid + 1) ans += ask(now * 2 + 1, mid + 1 ,r, nl, nr);
    return ans;
}

void treeChange(long long x, long long y, long long num)
{
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        change(1, 1, n, to_id[top[x]], to_id[x], num);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y]) swap(x, y);
    change(1, 1, n, to_id[x], to_id[y], num);
}

long long treeAsk(long long x, long long y)
{
    long long ans = 0;
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        ans += ask(1, 1, n, to_id[top[x]], to_id[x]);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y]) swap(x, y);
    ans += ask(1, 1, n, to_id[x], to_id[y]);
    return ans;
}

inline void treeRootChange(long long x, long long num)
{
    change(1, 1, n, to_id[x], siz[x] + to_id[x] - 1, num);
}

inline long long treeRootAsk(long long x)
{
    return ask(1, 1, n, to_id[x], siz[x] + to_id[x]- 1);
}

int main(int argc, char** argv)
{
    cin >> n >> m;

    for (long long i = 1; i <= n; i++)
        cin >> old[i];
    for (long long i = 0; i < n- 1; i++)
    {
        long long a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (long long i = 0; i < m; i++)
    {
        long long op;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            long long x, a;
            cin >> x >> a;
            treeChange(x, x, a);
            break;
        }
        case 2:
        {
            long long x, y;
            cin >> x >> y;
            treeRootChange(x, y);
            break;
        }
        case 3:
        {
            long long x;
            cin >> x;
            cout << treeAsk(1, x) << '\n';
            break;
        }
        }
    }
    return 0;
}