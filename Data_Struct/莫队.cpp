/**
 * @file 莫队.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief 离线算法，将提问的分布进行分块
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int maxn = 1E6 + 7;
const int T = 2000;
int n, m;

int a[maxn];
int pos[maxn];
int cnt[maxn];
int out[maxn];

struct node
{
    int l, r, k;
};
node q[maxn];
int ans = 0;
inline bool cmp(node& a, node& b)
{
    if (pos[a.l] != pos[b.l] ) return a.l < b.l;
    else if (pos[a.l] & 1) return a.r > b.r;
    return a.r < b.r;
}

void del(int x)
{
    cnt[a[x]] --;
    if (cnt[a[x]] == 0) ans --;
}

void add(int x)
{
    cnt[a[x]] ++;
    if (cnt[a[x]] == 1) ans ++;
}

int main(int argc, char** argv)
{
    cin >> n;
    int block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[i] = (i - 1) / block + 1;
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].l >> q[i].r;
        q[i].k = i;
    }

    sort(q + 1, q + m + 1, cmp);
    int l = 1, r= 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        out[q[i].k] = ans;
    }
    for (int i = 1; i <= m; i++)
        cout << out[i] << '\n';
    return 0;
}