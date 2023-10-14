#include <iostream>
#include <cmath>

using namespace std;

#define int long long
int get_phi(int num)
{
    // if (num == 1) return 0;

    int ans = 1;
    for (int i = 2; i * i <= num; i ++)
    {
        if (num % i == 0)
        {
            ans *= (i - 1);
            num /= i;
            while (num % i == 0)
            {
                ans = ans * i;
                num /= i;
            }
        }
    }

    if (num != 1)
        ans = ans * (num - 1);
    return ans;
}

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

void solve()
{
    int n, p;
    cin >> n >> p;

    int ans = 0;
    for (int i = 1; i * i <= n; i ++)
    {
        if (n % i == 0)
        {
            int j = n / i;
            ans = ans + qpow(n, n / i - 1, p) * get_phi(i);
        if (j != i)
            ans = ans + qpow(n, n / j - 1, p) * get_phi(j);
        }
    }

    cout << ans % p << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T --)
    {
        solve();
    }
}