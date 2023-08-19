#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
#define int long long
const int mod = 998244353;

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

void change(vector<int>& a, int len)
{
    for (int i = 1, j = len / 2, k; i < len - 1;  i ++)
    {
        if (i < j) swap(a[i], a[j]);
        k = len / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void ntt(vector<int>& a, int len, int i)
{
    change(a, len);

    for (int h = 2; h <= len; h <<= 1)
    {
        int gn = qpow(3, (mod - 1) / h);
        if (i == -1) gn = qpow(gn, mod - 2);
        for (int j = 0; j < len; j += h)
        {
            int g = 1;
            for (int k = j; k < j + h / 2; k ++)
            {
                int u = a[k], v = g * a[k + h / 2] % mod;
                a[k] = (u + v) % mod;
                a[k + h / 2] = (u - v + mod) % mod;
                g = g * gn % mod;
            }
        }
    }

    if (i == -1)
    {
        int inv = qpow(len, mod - 2);
        for (int i = 0; i < len; i ++)
            a[i] = a[i] * inv % mod;
    }
}

const int maxn = 1E5 + 7;
int fac[maxn];
int invfac[maxn];

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

int s[maxn];
int len = 1;

vector<int> divntt(int l, int r)
{
    if (l == r)
    {
        int tmp = 1;
        while (tmp <= s[l]) tmp <<= 1;
        vector<int> re(tmp + 1);

        re[0] = 0;
        for (int i = 1; i <= s[l]; i ++)
        {
            re[i] = c(s[l], i);
        }
        return re;
    }

    int mid = l + r >> 1;

    auto fl = divntt(l, mid);
    auto fr = divntt(mid + 1, r);

    int len = 1;
    while (len < fl.size() || len < fr.size()) len <<= 1;

    fl.resize(len + 1);
    fr.resize(len + 1);
    ntt(fl, len, 1);
    ntt(fr, len, 1);

    for (int i = 0; i <= len; i ++)
    {
        fl[i] = fl[i] * fr[i] % mod;
    }

    ntt(fl, len, -1);
    return fl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    initFacAndC(maxn - 7);
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i ++)
        cin >> s[i];

    vector<int> ans(divntt(1, m));

    cout << ans[k] << '\n';
}