#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int maxn = 1E5 + 7;
int trie[maxn << 4][2];
int ed[maxn << 4];
int a[maxn];
int cnt = 0;

inline void insert(int num)
{
    int p = 0;
    for (int i = 31; i >= 0; i --)
    {
        int tmp = ((num >> i) & 1);
        if (!trie[p][tmp]) trie[p][tmp] = ++ cnt;
        p = trie[p][tmp];
    }
    ed[p] ++;
}

inline int find(int num)
{
    int p = 0;
    int re = 0;
    for (int i = 31; i >= 0; i--)
    {
        int tmp = ((num >> i) & 1);
        if (trie[p][1 ^ tmp]) re += (1 << i), p = trie[p][1 ^ tmp];
        else  p = trie[p][tmp];
    }
    return re;
}

int main(int argc, char** argv)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        insert(a[i]);
    }
    
    int maxnn = 0;
    for (int i = 1; i <= n; i++)
        maxnn = max(maxnn, find(a[i]));
    cout << maxnn;
    return 0;
}