#include <iostream>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;
int l, r;
vector<int> isprime;
const int maxn = 1E5 + 7;
int fac[maxn];


void init()
{
    // O(nlogn) 用因子去筛区间合数
    for (int i = 2; i * i <= r; i ++)
        if (!fac[i])
        // (i + l - 1 ) / i * i 是大于l的第一个i的倍数
            for (int j = max(2, (l + i - 1) / i) * i; j <= r; j += i)
                isprime[j - l] = 1;
}

void init_fac()
{
    for (int i = 2; i * i <= maxn - 3; i ++)
        if (!fac[i])
            for (int j = i + i; j <= maxn; j += i)
                fac[j]  = 1;
}

void solve()
{
    cin >> l >> r;
    isprime.resize(r - l + 7);
    isprime.clear();

    if (l == 1)
        isprime[0] = 1;
    init();
    vector<int> ans;

    for (int i = l - l; i <= r - l; i ++)
    {
        if (!isprime[i])
            ans.push_back(i);
    }

    if (ans.size() <= 1)
        cout << "There are no adjacent primes.";
    else
    {
        int c1, c2, d1, d2;

        int minn = INT_MAX;
        int maxnn = 0;

        for (int i = 0; i < ans.size() - 1; i ++)
        {
            int num = ans[i + 1] - ans[i];

            if (minn > num)
            {
                c1 = ans[i], c2 = ans[i + 1];
                minn = num;
            }

            if (maxnn < num)
            {
                d1 = ans[i], d2 = ans[i + 1];
                maxnn = num;
            }
        }

        printf("%lld,%lld are closest, %lld,%lld are most distant.", c1 + l, c2 + l, d1 + l, d2 + l);
    }
}

signed main()
{
    init_fac();
    int T;
    cin >> T;
    while (T --)
    {
        solve();
    }
    return 0;
}