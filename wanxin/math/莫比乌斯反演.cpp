#include <iostream>
#include <cmath>
#include <map>

using namespace std;
#define int long long
const int maxn = 1E7 + 7;
int mu[maxn];
int isprime[maxn], prime[maxn];
int pre[maxn];
int cnt = 0;

void initmu(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i ++)
    {
        if (!isprime[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j ++)
        {
            isprime[i * prime[j]] = 1;
            mu[i * prime[j]] = mu[i] * -1;

            if (i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i ++)
        pre[i] = pre[i - 1] + mu[i];
}

int maxnn = 0;
int n, m;

int get_num(int d)
{
    int ans = 0, r = 0;
    for (int l = d; l <= maxnn; l = r + d)
    {
        r = min((n / (n / l) / d * d), (m / (m / l) / d * d));
        ans += (n / d) * (m / d) * (pre[r / d] - pre[l / d - 1]);
    }
    return ans;
}

void solve()
{
    cin >> n >> m;

    maxnn = max(n, m);
    int ans = 0;
    for (int i = 1; i <= cnt && prime[i] <= maxnn; i ++)
    {
        ans += get_num(prime[i]);
    }
    cout << ans ;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    initmu(maxn - 1);
    while (T --)
    {
        solve();
    }
    return 0;
}