#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;   

const int maxn = 3E4 + 7;
int n = 3E4 + 7;
int fa[maxn];
int front[maxn];
int num[maxn];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        num[i] = 1;
        front[i] = 0;
    }
}

int find(int a)
{
    if (a == fa[a])
        return a;
    int ffa = find(fa[a]);
    front[a] += front[fa[a]];
    return fa[a] = ffa;
}

void merge(int a, int b)
{
    int ffa = find(a), ffb = find(b);
    fa[ffb] = ffa;
    front[ffb] += num[ffa];
    num[ffa] += num[ffb];
    num[ffb] = 0;
}

int main(int argc, char** argv)
{
    init();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char c;
        int a, b;
        cin >> c;
        cin >> a >> b;
        if (c == 'M')
        {
            merge(a, b);
        }
        else 
        {
            if (find(a) != find(b))
                cout << "-1" << '\n';
            else 
                cout << abs(front[a] -front[b]) - 1<< '\n';
        }
    }
    return 0;
}