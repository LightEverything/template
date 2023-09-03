#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 5E4 + 7;
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
    {
        pre[i] = pre[i - 1] + mu[i];
    }
}

int a, b, c, d, k;

int get_num(int a, int b, int c)
{
    int ans = 0;
    int r = 0;
    int n = min(a, b);

    for (int l = c; l <= n; l = r + c)
    {
        r = min(a / (a / l) / c * c, b / (b / l) / c * c);
        ans += (pre[r / c] - pre[l / c - 1]) * (a / l) * (b / l);
    }

    return ans;
}

void solve()
{
    cin >> a >> b >> c >> d >> k;

    int gmax = min(b, d);
    int ans = get_num(b, d, k) - get_num(a - 1, d, k) - get_num(b, c - 1, k) + get_num(a - 1, c - 1, k);

    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    initmu(maxn - 1);
    while (T --)
    {
        solve();
    }
    return 0;
}