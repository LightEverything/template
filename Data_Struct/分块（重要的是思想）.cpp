/**
 * @file 分块（重要的是思想）.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief 分块模板不重要， 重要的是思想
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E5 + 7;
int a[maxn];
int n, m;
int add[maxn];
int st[maxn];
int ed[maxn];
int pos[maxn];
long long sum[maxn];
int block = 0;
int t = 0;

inline void init()
{
    block = sqrt(n);
    t = n / block + (n % block ? 1 : 0);

    for (int i = 1; i <= t; i++)
    {
        st[i] = (i - 1) * block + 1;
        ed[i] = i * block;
    }
    ed[t] = n;
    for (int i = 1; i <= n; i++)
        pos[i]=(i-1) / block + 1;
    for (int i = 1; i <= t; i++)
        for (int j = st[i]; j <= ed[i]; j++)
            sum[i] += a[j];
}

inline void change(int l, int r, int num)
{
    int p = pos[l], q = pos[r];
    if (p == q)
    {
        for (int i = l; i <= r; i++) a[i] += num;
        sum[p] += (r - l + 1) * num;
    }
    else 
    {
        for (int i = p + 1; i <= q - 1; i++) add[i] += num; 
        for (int i = l; i <= ed[p]; i++) a[i] += num;
        sum[p] += (ed[p] - l + 1) * num;
        for (int i = st[q]; i <= r; i++) a[i] += num;
        sum[q] += (r - st[q] + 1) * num;
    }
}


inline long long ask(int l, int r)
{
    int p = pos[l], q = pos[r];
    long long ans = 0;
    if (p == q)
    {
        for (int i = l; i <= r; i++) ans += a[i];
        ans += add[p] * (r - l + 1);
    }
    else 
    {
        for (int i = p + 1; i <= q - 1; i ++) ans += sum[i] + add[i] * (ed[i] - st[i] + 1);
        for (int i = l; i <= ed[p]; i ++) ans += a[i];
        ans += add[p] * (ed[p] - l + 1);
        for (int i = st[q]; i <= r; i ++) ans += a[i];
        ans += add[q] * (r - st[q] + 1);
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    init();
    for (int i = 1; i <= m; i++)
    {
        char c;
        int r, l;
        cin >> c>> l >> r;
        if (c == 'Q')
            cout << ask(l, r) << '\n';
        else 
        {
            int num;
            cin >> num;
            change(l, r, num);
        }
    }
    
    return 0;
}