#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct node
{
    int v, w;
    bool operator<(const node& a) const 
    {
        return w > a.w;
    }
};
const int maxn = 5E3 + 7;
int vis[maxn];
vector<node> e[maxn];
priority_queue<node> q;
int ans = 0;
int cnt = 1;

void prime()
{
    vis[1] = 1;
    for (auto it : e[1])
        q.push(it);

    while (!q.empty())
    {
        auto [v,w] = q.top(); q.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        ans += w;
        cnt ++;
        for (auto it : e[v])
        {
            int itv = it.v, itw = it.w;
            if (vis[itv]) continue;
            q.push(it);
        }
    }
}

int main(int argc, char** argv)
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back(node({v, w}));
        e[v].push_back(node({u, w}));
    }

    prime();
    if (cnt == n)
        cout << ans << '\n';
    else 
        cout << "orz" << '\n';
    return 0;
}