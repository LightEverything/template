#include <iostream>
#include <cmath>
#include <random>
#include <set>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

using i128 = __int128;
using ll = long long;

mt19937 engine(random_device{}());
uniform_int_distribution<long long> rd(1, LLONG_MAX);
const int prnum = 7;

ll qpow(ll a, ll b, ll mod)
{
    i128 tmp = a;
    i128 ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }

    return ans;
}

ll Pollard_rho(ll x)
{
    ll s = 0, t = 0;
    ll c = rd(engine) % (x - 1) + 1;

    int step = 0, goal = 1;
    ll val = 1;
    
    for (goal = 1;; goal *= 2, s = t, val = 1)
    {
        for (step = 1; step <= goal; ++ step)
        {
            t = ((i128)t * t + c) % x;
            val = (i128)val * abs(t - s) % x;
            if (step % ((1 << prnum) - 1) == 0)
            {
                ll d = __gcd(val, x);
                if (d > 1) return d;
            }
        }

        ll d = __gcd(val, x);
        if (d > 1) return d;
    }
}

bool Miller_Rabin(ll p)
{
    if (p < 2) return 0;
    if (p == 2) return 1;
    if (p == 3) return 1;

    ll d = p - 1, r = 0;

    while (!(d & 1)) ++ r, d >>= 1;
    for (ll k = 0; k < 10; k ++)
    {
        ll a = rd(engine) % (p - 2) + 2;
        ll x = qpow(a, d, p);
        if (x == 1 || x == p - 1) continue;

        for (int i = 0; i < r - 1; i ++)
        {
            x = (i128) x * x % p;
            if (x == p - 1) break;
        }
        if (x != p - 1)  return 0;
    }
    return 1;
}

vector<ll> ans;

void fac(ll n)
{
    if (n < 2)  return ;
    if (Miller_Rabin(n))
    {
        ans.push_back(n);
        return ;
    }

    ll p = n;
    while (p >= n) p = Pollard_rho(n);
    while (n % p == 0) n /= p;
    fac(n), fac(p);
}

void solve()
{
    ans.clear();
    ll num;
    cin >> num;

    if (Miller_Rabin(num)) cout << "Prime" << '\n';
    else 
    {
        fac(num);
        sort(ans.begin(), ans.end());
        cout << ans[ans.size() - 1] << '\n';
    }
}

int main()
{
    int T;
    cin >> T;
    while (T --)
    {
        solve();
    }
}