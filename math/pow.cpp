#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
long long quickPow(long long a, long long p)
{
    long long ans = 1, tmp = a;

    while (p)
    {
        if (p & 1)
            ans *= tmp;
        tmp *= tmp;
        p >>= 1;
    }
    return ans;
}

int main(int argc, char** argv)
{
    int a, p;
    cin >> a >> p;
    cout << quickPow(a, p);
    return 1;
}