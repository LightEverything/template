#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
const int maxn = 1E5 + 7;
int sg[maxn];
int a[maxn];
int maxnum = 0;

int getSg(int num)
{
    if (sg[num] != - 1) return sg[num];

    // vector<int> v;
    set<int> st;

    for (int i = 1; i * i <= num; i ++)
        if (num % i == 0)
        {
            st.insert(getSg(num - i));
            st.insert(getSg(num - num / i));
        }
    
    for (int i = 0;; i ++)
    {
        if (!st.count(i))
            return sg[num] = i;
    }
}


int main(int argc, char** argv)
{
    memset(sg, -1, sizeof sg);
    sg[0] = 0;

    int n;
    cin >> n;
    vector<vector<int>> v(n + 1);
    int sum = 0;

    for (int i =1; i <= n; i ++)
    {
        cin >> a[i];
        for (int j = 1; j * j <= a[i]; j ++)
        {
            if (a[i] % j == 0)
            {
                v[i].push_back(j);
                if (a[i] / j != j)
                    v[i].push_back(a[i] / j);
            }
        }

        sum ^= getSg(a[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i ++)
    {
        int tmp = sum ^ getSg(a[i]);

        for (auto it : v[i])
        {
            int sgg = getSg(a[i] - it);
            if ((sgg ^ tmp) == 0)
                ans ++;
        }
    }

    cout << ans << '\n';
    return 0;
}