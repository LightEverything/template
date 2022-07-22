#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E6 + 7;
int trie[maxn][30];
int ed[maxn * 30];
int cnt = 0;

void insert(string& s)
{
    int p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int tmp = s[i] - 'a';
        if (!trie[p][tmp]) trie[p][tmp] = ++ cnt;
        p = trie[p][tmp];
    }
    ed[p] ++;
}

int ask(string& s)
{
    int p = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int tmp = s[i] - 'a';
        if (!trie[p][tmp]) break;
        p = trie[p][tmp];
        ans += ed[p];
    }
    return ans;
}

int main(int argc, char** argv)
{   
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        insert(s);
    }

    for (int i = 1; i <= m; i++)
    {
        string s;
        cin >> s;
        cout << ask(s) << '\n';
    }

    return 0;
}