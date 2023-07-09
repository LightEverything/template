#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 1E7 + 7;

int isprime[maxn];
int prime[maxn];
int f[maxn];
int minnum[maxn];

int cnt = 0;

inline int calc_f(int a, int b)
{
    return b + 1;
}

void get_f()
{
    f[1] = 1;
    for (int i = 2; i <= maxn - 1; i ++)
    {
        if (!isprime[i]) 
        {
            prime[++cnt] = i;
            minnum[i] = 1;
            f[i] = calc_f(i, 1);
        }

        for (int j = 1; j <= cnt && prime[j] * i <= maxn - 1; j ++)
        {
            isprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                minnum[i * prime[j]] = minnum[i] + 1;
                f[i * prime[j]] = f[i] / calc_f(prime[j], minnum[i]) * calc_f(prime[j], minnum[i] + 1);
                break;
            }

            minnum[i * prime[j]] = 1;
            f[i * prime[j]] = f[i] * calc_f(prime[j], 1);
        }
    }
}

void solve()
{
    int num;
    cin >> num;

    cout << f[num] << '\n';
}

int main(int argc, char** argv)
{
    int q;
    cin >> q;
    get_f();
    while (q --)
    {
        solve();
    }
    return 0;
}