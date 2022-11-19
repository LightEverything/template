#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ull = unsigned long long ;
const int maxn = 1E5;
int base = 1233;
int cnt = 0;
ull mod = 212370440130137957ll;
// 大整数溢出
// inline ull gethash(string& str)
// {
//     ull ans = 0;
//     for (int i = 0; i < str.size(); i ++)
//     {
//         ans = ans * base + str[i];
//     }
//     return ans;
// }

inline ull gethash(string& str)
{
    ull ans = 0;
    for (int i = 0; i < str.size(); i ++)
    {
        ans = (ans * base + str[i]) % mod;
    }
    return ans;
}

int main(int argc ,char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 1; i <= n; i++)
    {
        cnt ++ ;
        string str;
        cin >> str;
        v.push_back(gethash(str));
    }
    int ans = 0;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i ++)
    {
        if (v[i] != v[i + 1])
            ans ++;
    }
    cout << ans << '\n';
    return 0;
}