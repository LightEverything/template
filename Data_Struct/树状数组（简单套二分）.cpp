/**
 * @file 树状数组（简单套二分）.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief 普通求和线段树
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

const int maxn = 2E5 + 7;
int n;
int tree[maxn];
int re[maxn];
pair<int, int> a[maxn];

inline int lowbit(int x)
{
    return x & -x;
}

inline int sum(int num)
{
    int ans = 0;
    for (int i = num; i ; i -= lowbit(i)) ans += tree[i];
    return ans;
}
inline void add(int pos , int num) 
{ 
    for (int i = pos; i <= n; i += lowbit(i)) tree[i] += num;
}

int main(int argc, char** argv)
{
    while (cin >> n)
    {
        // 初始化
        memset(tree, 0, sizeof tree);
        for (int i  =1; i <= n; i++)
        {
            cin >> a[i].first >> a[i].second;
            ++a[i].first;
            add(i, 1);

        }
        
        for (int i = n; i; i--)
        {
            int l = 1, r =n;
            // 普通二分
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (sum(mid) >= a[i].first)  r = mid;
                else l = mid + 1;            
            }
            re[l] = a[i].second;
            add(l, -1);
        }
        
        for (int i = 1; i <= n; i++)
            cout << re[i] << ' ';
        cout << '\n';
    }
    return 0;
}