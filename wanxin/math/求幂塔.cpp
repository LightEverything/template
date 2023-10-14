#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 1E7 + 7;
int isprime[maxn];
int prime[maxn];
int phi[maxn];
int cnt = 0;

#define int long long
int qpow(int a, int b, int m)
{
    int ans = 1;
    int tmp = a;

    while (b)
    {
        if (b & 1)
            ans = ans * tmp % m;
        tmp = tmp * tmp % m;
        b >>= 1;
    }
    return ans;
}

void init(int n)
{
    phi[1] = 1;
    for (int i = 2; i <= n; i ++)
    {
        if (!isprime[i]) prime[++cnt] = i, phi[i] = i - 1;

        for (int j = 1; j <= cnt && i * prime[j] <= n; j ++)
        {
            isprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}

int dfs(int num)
{
    if (num == 1)
        return 1;
    int nex = dfs(phi[num]);
    if (!nex) nex = phi[num];
    int p = qpow(2, nex, num) % num;
    return p;
}

void solve()
{
    int n;
    cin >> n;
    // 2 的幂塔
    cout << dfs(n) << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    init(1E7);
    int T;
    cin >> T;
    while (T --)
    {
        solve();
    }
    return 0;
}