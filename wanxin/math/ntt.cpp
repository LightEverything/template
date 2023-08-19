#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>

using namespace std;

#define int long long

const int mod = 998244353;

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

void change(int a[], int len)
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

void ntt(int a[], int len, int i)
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

const int maxn = 5E4 + 7;
int fa[maxn * 4], fb[maxn * 4];
int sum[maxn * 4];

signed main()
{
    string a, b;
    cin >> a >> b;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int len = 1;

    while (len < a.size() * 2|| len < b.size() * 2) len <<= 1;
    for (int i = 0; i < len; i ++)
    {
        if (i < a.size())
            fa[i] = (a[i] - '0');
        else 
            fa[i] = (0);

        if (i < b.size())
            fb[i] = (b[i] - '0');
        else 
            fb[i] = (0);
    }

    ntt(fa, len, 1);
    ntt(fb, len, 1);

    for (int i = 0; i < len; i ++) fa[i] = (fa[i] + fb[i]) % mod;
    ntt(fa, len, -1);


    for (int i = 0; i < len; i ++)
        sum[i] = fa[i];

    for (int i = 0; i < len; i ++)
    {
        sum[i + 1] += sum[i] / 10;
        sum[i] %= 10;
    }

    bool flag = false;
    for (int i = len; i >= 0; i --)
    {
        if (sum[i])
            flag = true;
        if (flag)
            cout << sum[i];
    }
    if (!flag)
        cout << 0 << '\n';
    return 0;
}