#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 1E5 + 7;

bool isprime[maxn];
int prime[maxn];
int cnt = 0;

void init()
{
    for (int i = 2; i <= maxn; i ++)
    {
        if (isprime[i] == 0) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j ++)
        {
            isprime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main(int argc, char** argv)
{
    init();
    return 0;
}