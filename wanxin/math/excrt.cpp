#include <iostream>
#include <cmath>

using namespace std;

#define int long long
const int maxn = 1E5 + 7;
int p[maxn];
int a[maxn];
int r[maxn];
int n;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

inline int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int exgcd(int a, int b, int& x, int& y)
{
    if (!b)
        return x = 1, y = 0, a;
    int ans = exgcd(b, a % b, y, x);
    y = y - a / b * x;
    return ans;
}

// 从一开始 aix === ri (mod pi)
int excrta()
{
    for (int i = 1; i <= n; i ++)
    {
        int x, y;
        int g = exgcd(a[i], p[i], x, y);
        if (r[i] % g) 
            return -1;

        int bg = p[i] / g;
        x = (x * (r[i] / g) % bg + bg) % bg;
        r[i] = x, p[i] = bg;
    }

    int now_p = p[1], now_r = r[1];
    for (int i = 2; i <= n; i ++)
    {
        // x = x0 (mod lcm(m1, m2)) x0 是exgcd的解
        int x, y;
        int g = exgcd(now_p, p[i], x, y);
        if ((r[i] - now_r) % g != 0)    
            return -1;

        int tmpp = lcm(now_p, p[i]);
        x = x * (r[i] - now_r) / g % (p[i] / g);
        now_r = (x * now_p % tmpp + now_r) % tmpp;
        now_p = tmpp;
        now_r = ((now_r % now_p) + now_p) % now_p;
    }

    return now_r;
}

signed main()
{
    cin >> n;

    for (int i = 1; i <= n; i ++)
    {
        cin >> p[i] >> r[i];
        a[i] = 1;
    }
    int x = excrta();
    cout << x;
    return 0;
}