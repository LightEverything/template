/**
 * @file codeforceModel.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief codeforces的答题模板
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <cstring>
#include <random>
#include <climits>
 
using namespace std;
 
#define random
 
const int maxn = 2E5 + 7;
#define int long long
vector<int> e[maxn];
int dp[maxn];
int hhash[maxn];
 
#ifdef random
mt19937 engine(random_device{}());
uniform_int_distribution<long long> rd(1, LLONG_MAX);
#endif
 
int base = rd(engine);
 
inline void init(int n)
{
    for (int i = 1; i <= n; i ++)
    {
        e[i].clear();
        dp[i] = 0;
    }
}
 
int confound(int x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
 
void dfs(int now, int fa)
{
    hhash[now] =  base;
    int sum = 0;
    int siz = e[now].size() - (now == 1 ? 0 : 1);
    map<int, int> mp;
 
    for (auto& y : e[now])
    {
        if (y == fa) continue;
        dfs(y, now);
        sum ^= hhash[y];
        mp[hhash[y]] = y;
        hhash[now] +=  confound(hhash[y]);
    }
 
    hhash[now] = hhash[now] ^ (1 << 20 - 1);
 
    if (sum == 0)
    {
        dp[now] = true;
    }
    else
    {
        if (siz % 2 == 1 && dp[mp[sum]])
            dp[now] = true;
        else 
            dp[now] = false;
    }
}
 
inline void solve()
{
#ifdef DEBUG
    for (int i = 1; i <= 100; i++);
#endif
    int n;
    cin >> n;
    
    init(n);
    for (int i = 1; i <= n - 1; i ++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
 
    dfs(1, -1);
    cout << (dp[1] ? "YES" : "NO") << '\n';
}
 
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}