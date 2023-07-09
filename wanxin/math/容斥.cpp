#include <iostream>
#include <cmath>

using namespace std;
#define int long long
int a[] = {2, 5, 11, 13};
int n;

void solve()
{
    int ans = n;
    for (int i = 1;i < (1 << 4); i ++)
    {
        int tmp = 1, many = 0;
        for (int j = 0; j <= 3; j ++)
        {
            if ((1LL << j) & i)  
            {
                many ++;
                tmp *= a[j];
            }
        }
        if (many & 1)
            ans -= (n / tmp);
        else 
            ans += (n / tmp);
    }
    cout << ans << '\n';
}
signed main()
{
    while (cin >> n)
    {
        solve();
    }
}