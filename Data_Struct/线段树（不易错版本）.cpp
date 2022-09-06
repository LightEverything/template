/**
 * @file 线段树（不易错版本）.cpp
 * @author lightEvething (wanxinnb@outlook.com)
 * @brief  使用一些宏定义和结构体使得线段树出错概率减少
 * @date 2022-09-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>

const int maxn = 1E5 + 7;

#define rhs now * 2 + 1
#define lhs now * 2
#define lls tree[now].l
#define rrs tree[now].r

using namespace std;
struct node 
{
    long long l, r, x;
};
node tree[maxn << 2];
long long lazy[maxn << 2];
int a[maxn];


inline void up(int now) { tree[now].x = tree[lhs].x + tree[rhs].x; }

void build(int now, int l, int r)
{
    lls = l, rrs = r;
    if (l == r)
    {
        tree[now].x = a[l];
        return ;
    }

    int mid = (lls + rrs) / 2;
    build(lhs, l, mid);
    build(rhs, mid + 1, r);
    up(now);
}

void update(int now)
{
    int mid = (lls + rrs) / 2;
    tree[lhs].x += lazy[now] * (mid - lls+ 1), tree[rhs].x += lazy[now] * (rrs - mid);
    lazy[lhs] += lazy[now], lazy[rhs] += lazy[now];
    lazy[now] = 0;
}

void change(int now, int nl, int nr, int num)
{
    if (nl <= tree[now].l && nr >= tree[now].r)
    {
        lazy[now] += num;
        tree[now].x += num * (tree[now].r - tree[now].l + 1);
        return ;
    }
    if (lazy[now]) update(now);
    int mid = (lls + rrs) / 2;
    if (nl <= mid) change(lhs, nl, nr, num);
    if (nr >= mid + 1) change(rhs, nl, nr, num);
    up(now);
}

long long answer(int now, int nl, int nr)
{
    if (nl <= lls && nr >= rrs)
    {
        return tree[now].x;
    }
    if (lazy[now])  update(now);
    long long ans = 0;
    int mid = (lls + rrs) / 2;
    if (nl <= mid) ans += answer(lhs, nl, nr);
    if (nr >= mid + 1) ans += answer(rhs, nl, nr);
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++)
        cin >> *(a + i);
        
    build(1, 1, n);

    while (m --)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            change(1, x, y, k);
        }
        else 
        {
            int x, y;
            cin >> x >> y;
            cout << answer(1, x, y) << '\n';
        }
    }
    return 0;
}