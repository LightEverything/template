#include <iostream>
#include <cmath>

using namespace std;
const int mod = 1E9 + 7;

long long qpow(long long a, long long b)
{
    long long ans = 1;
    long long tmp = a;

    while (b)
    {
        if (b & 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }
    return ans;
}

const int maxn = 2E5 + 7;
long long fac[maxn];
long long invfac[maxn];

inline void initFacAndC(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; i ++)
        fac[i] = fac[i - 1] *i % mod;
    invfac[n] = qpow(fac[n], mod - 2);
    invfac[0] = 1;

    for (int i = n - 1; i >= 1; i --)
        invfac[i] = (i + 1) * invfac[i + 1] % mod;
}


long long get_stl2(int n, int m)
{

    long long ans = 0;
    for (int i = 0; i <= m; i ++)
    {
        long long tmp = ((m - i) % 2 == 0?  1 : -1);
        tmp = (tmp * qpow(i, n) % mod + mod) % mod;
        tmp = tmp * invfac[i] % mod * invfac[m - i] % mod;
        ans = (ans + tmp ) % mod;
    }

    return ans;
}

int main()
{
    int n, k;
    cin >> n >> k;

    initFacAndC(n);
    long long sum = 0;
    for (int i = 1; i <= n; i ++)
    {
        int tmp;
        cin >> tmp;
        sum += tmp;
        sum %= mod;
    }

    long long stlsum = 0;
    stlsum = get_stl2(n, k) + get_stl2(n - 1, k) * (n - 1) % mod;

    stlsum %= mod;
    sum = sum * stlsum % mod;
    cout << sum << '\n';
    return 0;
}