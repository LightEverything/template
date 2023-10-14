#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const int maxn = 3E2 + 7;
double x2[maxn];
double x1[maxn];
double dp[maxn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string str;
    cin >> str;
    dp[0] = 0;

    for (int i = 1; i <= str.size(); i ++)
    {
        if (str[i - 1] == 'o')
        {
            x1[i] = (x1[i - 1] + 1);
            x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1);
            dp[i] = (dp[i - 1] + 2 * x1[i - 1] + 1);
        }
        else if (str[i - 1] == 'x')
        {
            dp[i] = dp[i - 1];
            x1[i] = 0, x2[i] = 0;
        }
        else 
        {
            x1[i] = (x1[i - 1] + 1) * 0.5;
            x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1) * 0.5;
            dp[i] = dp[i - 1] * 0.5 + 0.5 * (dp[i - 1] + 2 * x1[i - 1] + 1);
        }
    }

    cout <<fixed << setprecision(4) << dp[str.size()] << '\n';
}