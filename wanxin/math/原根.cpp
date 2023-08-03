#include <iostream>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;
#define int long long
const int maxn = 1E6 + 7;
int ans[maxn];

int get_phi(int a)
{
    int ans = 1;

    for (int i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            ans *= (i - 1);
            a /= i;
            while (a % i == 0)
            {
                a /= i;
                ans *= i;
            }
        }
    }

    if (a != 1)
        ans *= (a - 1);

    return ans;
}

int qpow(int a, int b, int mod)
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

void solve()
{
    int cnt = 0;
    map<int, int> mp;
    int n, d;
    cin >> n >> d;

    int num = get_phi(n);
    int tmp = num;

    int minrt = 0;
    for (int i = 2; i * i <= tmp; i++)
    {
        while (tmp % i == 0)
        {
            mp[i]++;
            tmp /= i;
        }
    }

    if (tmp != 1)
        mp[tmp]++;

    for (int g = 1; g <= n; g++)
    {
        if (__gcd(g, n) != 1)
            continue;

        bool flag = true;
        for (auto i : mp)
        {
            if (qpow(g, num / i.first, n) == 1)
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            minrt = g;
            break;
        }
    }

    if (minrt == 0)
        cout << 0 << '\n'
             << '\n';
    else
    {
        int prod = 1;
        for (int i = 1; i <= num; i++)
        {
            prod = (1ll * prod * minrt) % n;
            if (__gcd(i, num) == 1)
            {
                ans[++cnt] = prod;
            }
        }
        sort(ans + 1, ans + 1 + cnt);
        cout << cnt << '\n';
        for (int i = d; i <= cnt; i += d)
        {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}