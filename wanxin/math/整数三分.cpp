#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 1E5 + 7;
int mu[maxn];
int isprime[maxn];
int prime[maxn];
int cnt = 0;
int n;

int g(int x)
{
    int ans = 0;
    for (int i = x; i <= n; i += x)
        ans += n / i;
    return 2 * ans;
}

int g1(int x)
{
    return (n / x) * (n / x);
}

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

    // for (int i = 1; i <= n; i ++)
    //     pre[i] = pre[i - 1] + mu[i];
}
int main()
{
    cin >> n;

    initmu(n);

    int ans = 0;
    for (int i = 1; i <= n; i ++)
        ans += mu[i] * g(i);
    for (int i = 1; i <= n; i ++)
        ans -= mu[i] * g1(i);
    cout << n * n - ans << '\n';
    return 0;
}