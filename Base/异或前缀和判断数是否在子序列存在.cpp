#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
#define int long long
const int maxn = 1E6 + 7;

int cnt[2 * maxn];
int sum[maxn];

void solve()
{
    int n;
    cin >> n;

    for (int i = 0; i <= 2 * n; i ++)
        cnt[i] = 0;

    for (int i = 1; i <= n; i ++)
    {
        int tmp;
        cin >> tmp;
        sum[i] = sum[i - 1] ^ tmp;
    }

    int ans = 0;
    for (int i = 1; i <= n; i ++)
    {
        cnt[sum[i - 1]] ++;
        for (int j = 0; j * j < 2 * n; j ++)
            ans += cnt[sum[i] ^ (j * j)];
    }
    cout << n * (n + 1) / 2 - ans << '\n';
}

signed main()
{
    int T;
    cin >> T;
    while (T --)
    {
        solve();
    }
    return 0;
}