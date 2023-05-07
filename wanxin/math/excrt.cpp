#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 1E5 + 7;
int p[maxn];
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

int excrt()
{
    int now_p = p[1], now_r = r[1];

    for (int i = 2; i <= n; i ++)
    {
        // x = x0 (mod lcm(m1, m2)) x0 是exgcd的解
        int x, y;
        int g = exgcd(now_p, p[i], x, y);
        if ((r[i] - now_r) % g != 0)    return -1;
        now_r = x * (r[i] - now_r) / g * now_p + now_r, now_p = lcm(now_p, p[i]);
        now_r = ((now_r % now_p) + now_p) % now_p; // 未经检验
    }

    return now_r;
}

int main(int argc, char** argv)
{
    cin >> n;

    for (int i = 1; i <= n; i ++)
        cin >> p[i] >> r[i];
    int x = excrt();
    cout << x;
    return 0;
}