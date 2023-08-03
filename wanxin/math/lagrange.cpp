#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
#define int long long

const int mod = 9999991;
const int maxn = 1E3 + 7;
int invfac[maxn];
int fac[maxn];
int x[maxn], y[maxn];

int qpow(int a, int b)
{
    int tmp = a;
    int ans = 1;

    while (b)
    {
        if (b & 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }
    return ans;
}

void init(int n)
{
    fac[0] = 1;

    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;

    invfac[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i --)
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
    invfac[0] = 1;
}

// x从0开始储存, 多项式次数为n, x[] 是连续整数
int lagrange(int n, int x[], int y[], int k, int mod)
{
    vector<int> pre(n + 5), suf(n + 5);

    pre[0] = (k - x[0] + mod) % mod;
    suf[n + 1] = 1;
    for (int i = 1; i <= n; i ++) 
        pre[i] = pre[i - 1] * (k - x[i] + mod) % mod;
    for (int i = n; i >= 0; i --)
        suf[i] = suf[i + 1] * (k - x[i] + mod) % mod;

    int ans = 0;
    for (int i = 0; i <= n; i ++)
    {
        int up = (i == 0 ? 1 : pre[i - 1]) * suf[i + 1] % mod;
        int down = (invfac[n - i] * invfac[i] % mod * ((n - i) % 2 == 0 ? 1 : -1) + mod ) % mod;

        ans = (ans + y[i] * down % mod * up % mod + mod) % mod;
    }
    return ans;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; i ++)
    {
        x[i] = i;
        cin >> y[i];
    }

    x[n + 1] = n + 1;
    y[n + 1] = lagrange(n, x, y, n + 1, mod);

    for (int i = 1; i <= n + 1; i ++)
        y[i] = (y[i] + y[i - 1]) % mod;

    while (m --)
    {
        int l, r;
        cin >> l >> r;
        cout << (lagrange(n + 1, x, y, r, mod) - lagrange(n + 1, x, y, l - 1, mod) + mod) % mod << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    init(1000 + 4);
    while (T --)
    {
        solve();
    }
    return 0;
}