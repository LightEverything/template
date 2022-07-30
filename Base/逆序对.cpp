#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 5E5 + 7;
int n;
int a[maxn];
int sorta[maxn];
int tree[maxn];
int cnt = 0;
unordered_map<int , int> mp;
long long ans = 0;

inline int lowbit(int x)
{
    return x & -x;
}

void insert(int x, int num)
{
    for (int i = x; i <= n; i += lowbit(i)) tree[i] += num;
}

int getsum(int x)
{
    int tmp = 0;
    for (int i = x; i ; i -= lowbit(i)) tmp += tree[i];
    return tmp;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sorta[i] = a[i];
    }

    sort(sorta + 1, sorta + n + 1);

    // 离散化
    for (int i = 1; i <= n; i++)
    {
        if (!mp[sorta[i]]) mp[sorta[i]] = ++cnt;
    }

    for (int i = 1; i <= n; i++)
    {   
        int x = mp[a[i]];
        insert(x, 1);
        ans += i - getsum(x);
    }

    cout << ans;
    return 0;
}