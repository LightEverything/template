#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
struct node 
{
    int v, w;
};

bool operator<(const node& a, const node& b)
{
    // 注意是>
    return a.w > b.w;
}

const int maxn = 1E5 + 7;
vector<node> e[maxn];
int dis[maxn];
int vis[maxn];
int n, m, s;

void init()
{
    for (int i = 1; i <= n; i ++)
        dis[i] = 0x7fffffff;
}

void dijkstra(int now, int fa)
{
    init();
    priority_queue<node> pq;
    pq.push(node({now, 0}));
    dis[now] = 0;

    while (!pq.empty())
    {
        auto [v, w] = pq.top();pq.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        for (auto& it : e[v])
        {
            int tv = it.v, tw = it.w;
            if (dis[tv] >  w + tw)
            {
                dis[tv] = w + tw;
                if (!vis[tv])
                    pq.push(node({tv, dis[tv]}));
            }
        }
    }

}

int main(int argc, char** argv)
{
    cin >> n >> m >> s;

    for (int i = 1; i <= m; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(node({v, w}));
    }

    dijkstra(s, -1);
    for (int i = 1; i <= n; i ++)
        cout << dis[i] << ' ';
    return 0;
}