#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 2E5 + 7;
const int mod = 1E9 + 7;

int fac[maxn];
int invfac[maxn];

inline int qpow(int a, int b)
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


inline int c(int a, int b)
{
    if (a < b || a < 0 || b < 0)
        return 0;
    return fac[a] * invfac[b] % mod * invfac[a - b] % mod;
}