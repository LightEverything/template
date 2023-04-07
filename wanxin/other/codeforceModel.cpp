/**
 * @file codeforceModel.cpp
 * @author lighteverthing (wanxinnb@outlook.com)
 * @brief codeforces的答题模板
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <cstring>
#include <random>
#include <climits>

using namespace std;

#ifdef  RANDOM 
mt19937 engine(random_device{}())
uniform_int_distribution<long long> rd(1, LLONG_MAX);
#endif

inline void solve()
{
#ifdef DEBUG
    for (int i = 1; i <= 100; i++);
#endif
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}