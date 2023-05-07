#include <iostream>
#include <cmath>

using namespace std;
const int maxn = 3E6 + 7;
int inv[maxn];

int main(int argc, char** argv)
{
    int n, p;
    cin >> n >> p;

    inv[1] = 1;
    for (int i = 2; i <= n; i ++)
        // -kj' = - (p / i) * inv[p % i]
        inv[i] = ((p - p / i ) * inv[p % i]) % p;
    
    for (int i = 1; i <= n; i ++)
        cout << inv[i] << '\n';
    return 0;
}