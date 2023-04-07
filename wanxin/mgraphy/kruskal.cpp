#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 5E3 + 7;
const int maxnn = 2E5 + 7;
struct node
{
    int u, v, w;
};
node e[maxnn];
int fa[maxn];
int n, m;

void init()
{
    for (int i = 1; i <= n; i ++)
        fa[i] = i;
}

int find(int a)
{
    return fa[a] == a ? a : fa[a] = find(fa[a]);
}

void merge(int a, int b)
{
    int ffb = find(b), ffa = find(a);
    fa[ffa] = ffb;
}

bool cmp(node& a, node& b)
{
    return a.w < b.w;
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    init();
    for (int i = 1;i <= m; i ++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        e[i] = {x, y, w};
    }
    sort(e + 1, e + 1 + m, cmp);

    int ans = 0;
    for (int i = 1; i <= m; i ++)
    {
        auto [u, v, w] = e[i];
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        ans += w;
        merge(u, v);
    }

    bool flag = false;
    int pre = find(1);
    for (int i = 2; i <= n; i ++)
    {
        if (find(i) != pre)
            flag = true;
    }

    if (!flag)
        cout << ans;
    else 
        cout << "orz";
    return 0;
}