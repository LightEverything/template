#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double a[20];

double qpow(double a, int b)
{
    double ans = 1;
    double tmp = a;
    while (b)
    {
        if (b & 1)
            ans = tmp * ans;
        tmp = tmp * tmp;
        b >>= 1;
    }
    return ans;
}

int n;
double l, r;
const double eps = 1E-9;

double f(double x)
{
    double ans = 0;
    for (int j = n; j >= 0; j --)
    {
        ans += a[j] * qpow(x, j);
    }
    return ans;
}

int main()
{
    cin >> n >> l >> r;

    for (int j = n; j >= 0; j --)
        cin >> a[j];
    // cout << f(-0.9981) << '\n';
    while (r - l > eps)
    {
        double mid = (r - l) / 3;
        double mid1 = l + mid, mid2 = r - mid;
        if (f(mid1) > f(mid2))
            r = mid2;
        else 
            l = mid1;
    }

    cout << fixed << setprecision(9) << l << '\n';
}