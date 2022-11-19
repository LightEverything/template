#include <iostream>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <algorithm>

using namespace std;

template<typename T>
class FenwickTree
{
public:
    static constexpr int maxn = 1E5 + 7;
    T tree[maxn] = {0};
    int rg;

    FenwickTree(int rg)
    {
        this->rg = rg;
    }

    void add(int pos, T num)
    {
        for (int i = pos; i <= rg; i += lowBit(i)) tree[i] += num;
    }

    T query(int pos)
    {
        T ans = 0;
        for (int i = pos; i ; i -= lowBit(i)) ans += tree[i];
        return ans;
    }

    int lowBit(int x)
    {
        return x & (-x);
    }
};