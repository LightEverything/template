#include <iostream>
#include <cmath>

using namespace std;

int exgcd(long long a, long long b, long long & x, long long & y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int ans = exgcd(b, a % b, y, x);
    y = y - a /b * x;
    return ans;
}

int main(int argc, char** argv)
{
    long long a, b;
    cin >> a >> b;
    long long ansx = 0, ansy = 0;
    exgcd(a, b, ansx, ansy);
    
    while (ansx < 0) ansx += b;
    while (ansx - b > 0) ansx -= b;
    cout << ansx;
    return 0;
}