#include <iostream>
#include <cmath>
#include <map>
#include <unordered_map>
using namespace std;
 
// #define int long long
unordered_map<int, int> mp;
const int maxn = 1E5 + 7;
int a[maxn];
 
inline int mod(long long a, long long b)
{
    return a < b ? a : a % b + b;
}
 
 // exphi : a ^ b = a ^ (b % phi(m) + phi(m)) (mod m)
int phi(int a)
{
    // 记忆化
    if (mp[a]) return mp[a];
    int ans = 1;
    for (int i = 2; i * i <= a; i ++)
    {
        if (a % i == 0)
        {
            ans *= (i - 1);
            a /= i;
            while (a % i == 0)
                a /= i, ans *= i;
        }
    }
    if (a > 1)
        ans *= (a - 1);
    return mp[a] = ans;
}
 
int qpow(int a, int b, int m)
{
    long long ans = 1;
    long long tmp = a;
    while (b)
    {
        if (b & 1)
            ans =  mod(ans * tmp, m);
        tmp = mod(tmp * tmp, m);
        b >>= 1;
    }
    return ans;
}
 
int solve(int l, int r, int m)
{
    if (l == r || m == 1) return (a[l] < m ? a[l] : a[l] % m + m);
 
    return qpow(a[l], solve(l + 1, r, phi(m)), m);
}
 
signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i];
    int q;
    cin >> q;
    while (q --)
    {
        int l, r;
        cin >> l >> r;
        cout << solve(l, r, m) % m<< '\n';
    }
 
    return 0;
}
