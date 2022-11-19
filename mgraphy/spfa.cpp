#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
struct node
{
    int v, w;
};
const int maxn = 2E3 + 7;
vector<node> e[maxn];
int cnt[maxn];
int dis[maxn];
int vis[maxn];
int n, m;

void init()
{
    fill(dis + 1, dis + 1 + n, 1E9 + 7);
    memset(vis, 0, sizeof vis);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++)
        e[i].clear();
    dis[1] = 0;
}

bool spfa()
{
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int v = q.front(); q.pop();
        vis[v] = 0;
        for (auto it : e[v])
        {
            int tv = it.v, tw = it.w;
            if (dis[v] + tw < dis[tv])
            {
                dis[tv] = dis[v] + tw;
                cnt[tv] = cnt[v] + 1;
                if (!vis[tv])
                    q.push(tv);
                vis[tv] = 1;
            }
            if (cnt[tv] >= n)
                return true;
        }
    }
    return false;
}

void sovle()
{
    cin >> n >> m;
    init();

    for (int i = 1; i <= m; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(node({v, w}));
        if (w >= 0)
            e[v].push_back(node({u, w}));
    }

    if (spfa())
        cout << "YES" << '\n';
    else 
        cout << "NO" << '\n';
}

int main(int argc, char** argv)
{
    int T;
    cin >> T;
    while (T --)
    {
        sovle();
    }
    return 0;
}