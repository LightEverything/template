#include <iostream>
#include <cmath>
#include <map>

using namespace std;
const int maxn = 15;
const int mod = 2004;
int f[maxn];
int fac = 1;
map<int, int> mp;
int n, a, b;

void gen(int pos, int coff, int index)
{
    if (pos == n)
    {
        (mp[index] += coff) %= mod;
        return ;
    }
    gen(pos + 1, coff, index);
    gen(pos + 1, (coff * -1 + mod) % mod, index + f[pos + 1] + 1);
}

int inv = 0;

int qpow(int a, int b)
{
    int ans=  1;
    int tmp = a;
    while (b)
    {
        if (b & 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }
    return ans;
}

int c(int a, int b)
{
    if (a < b || a < 0)
        return 0;
    int ans = 1;
    // mod先乘除数，最后一起除掉
    int tmp_mod = mod * fac;
    
    for (int i = a - b + 1; i <= a; i ++)
    {
        ans = ans * i % tmp_mod;
    }
    return (ans / fac) % mod;
}

void solve()
{
    cin >> n >> a >> b;

    for (int i = 1; i <= n; i ++)
    {
        cin >> f[i];
        fac *= i;
    }

    gen(0, 1, 0);

    int ans = 0;
    for (auto it : mp)
    {
        int tmp = c(n + b - it.first, n) - c(n + a - it.first - 1, n) + mod;
        tmp %= mod;
        (ans += it.second * tmp % mod) %= mod;
    }
    cout << ans << '\n';
}

int main()
{

    solve();
    return 0;
}