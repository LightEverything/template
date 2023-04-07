/**
 * @file 线段树.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief  普通线段树，不带结构体
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

using namespace std;

const int maxn= 1E5 + 7;
int a[maxn];
long long tree[maxn * 4];
int lazy[maxn * 4];
int n;

void build(int now, int l, int r)
{
    if (l == r)
    {
        tree[now] = a[l];
        return ;
    }
    int mid = (l + r) / 2;
    build(now * 2, l ,mid);
    build(now * 2 + 1, mid + 1, r);
    tree[now] = tree[now * 2] + tree[now * 2 +1];
}

void update(int now, int l, int r)
{
    lazy[now * 2] += lazy[now];
    lazy[now * 2 + 1] += lazy[now];
    int mid = (l + r) / 2;
    tree[now * 2] += lazy[now] * (mid - l + 1);
    tree[now * 2 + 1] += lazy[now] * (r - mid);
    lazy[now] = 0;
}

void change(int now, int l, int r, int nl, int nr, int num)
{
    if (nl <= l && nr >= r)
    {
        lazy[now] += num;
        tree[now] += num * (r- l + 1);
        return ;
    }
    if (lazy[now] != 0)
        update(now, l, r);

    int mid = (l + r) / 2;
    if (nl <= mid) change(now * 2, l, mid, nl, nr, num);
    if (nr >= mid + 1) change(now * 2 + 1, mid + 1, r, nl, nr, num);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

long long answer(int now, int l, int r, int nl, int nr)
{
    if (nl <= l && nr >= r)
    {
        return tree[now];
    }

    if (lazy[now] != 0)
    {
        update(now, l, r);
    }
    int mid = (l + r) / 2;
    long long ans = 0;
    if (nl <= mid) ans += answer(now * 2, l, mid, nl, nr);
    if (nr >= mid + 1) ans += answer(now * 2 + 1, mid + 1, r, nl, nr);
    return ans;
}

int main(int argc, char** argv)
{
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build(1, 1, n);

    for (int i = 0; i < m; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            change(1, 1, n, x, y, k);
        }
        else 
        {
            int x, y;
            cin >> x >> y;
            cout << answer(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}