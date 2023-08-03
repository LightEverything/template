#include <iostream>
#include <cmath>
#include <map>

using namespace std;
#define int long long
int bsgs(int a, int b, int p)
{
    int n = sqrt(p) + 1, bs = 1;
    map<int, int> mp;

    for (int i = 1; i <= n; i ++)
    {
        bs = bs * a % p;
        mp[b * bs % p] = i;
    }

    int gs = bs;
    for (int i = 1; i <= n; i ++)
    {
        auto it = mp.find(gs);
        if (it != mp.end())
            return i * n - (it->second);
        gs = gs * bs % p;
    }
    return -1;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c;
    cin >> c >> a >> b;
        int ans = bsgs(a, b, c);
        if (ans > 0)
            cout << ans << '\n';
        else 
            cout << "no solution" << '\n';
    return 0;
}