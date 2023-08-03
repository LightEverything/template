#include <iostream>
#include <cmath>

using namespace std;

int get_phi(int a)
{
    int ans = 1;

    for (int i = 2; i * i <= a; i ++)
    {
        if (a % i == 0)
        {
            ans *= (i - 1);
            a /= i;
            while (a % i == 0)
            {
                a /= i;
                ans *= i;
            }
        }
    }

    if (a != 1)
        ans *= (a - 1);

    return ans;
}

int main()
{
    int n;
    cin >> n;
    cout << get_phi(n);
    return 0;
}