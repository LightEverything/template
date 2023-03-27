#include <iostream>
#include <unordered_map>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 1E4 + 7;
struct node
{
    int v, w;
};

vector<node> e[maxn];

int gravity = 0;
int gravity_siz[maxn] = {0}; // 以x为重心的树大小
int siz = 0, mx = 0, cnt;
int vis[maxn], bt[maxn];
map<int, int> ans;
node num[maxn];
vector<int> qs;
int n;

bool cmp(node& a, node& b)
{
    if (a.w != b.w)
        return a.w < b.w;
    else 
        return a.v > b.v;
}

// 注意，修改的都是全局变量
void getSize(int now, int fa)
{
    siz ++;
    for (auto& it : e[now])
    {
        auto [y, w] = it;
        if (y == fa || vis[y]) continue;
        getSize(y, now);
    }
}

void getGravity(int now,int fa)
{
    gravity_siz[now] = 1;
    int tmp = 0;
    for (auto& it : e[now])
    {
        auto [y, w] = it;

        if (y == fa || vis[y]) continue;
        getGravity(y, now);
        gravity_siz[now] += gravity_siz[y];
        tmp = max(tmp, gravity_siz[y]);
    }
    tmp = max(tmp, siz - gravity_siz[now]);
    if (gravity == 0 || tmp < mx)
    {
        mx = tmp;
        gravity = now;
    }
}

void getAns(int now, int fa)
{
    sort(num + 1, num + 1 + cnt, cmp);
    for (auto q : qs)
    {
        int l = 0, r = cnt;
        if (ans[q]) continue;
        while (l < r)
        {
            if (num[l].w + num[r].w < q) l ++;
            else if (num[l].w + num[r].w > q) r --;
            else if (bt[num[l].v] == bt[num[r].v])
            {
                if (num[r].w == num[r - 1].w) r --;
                else l ++;
            }
            else 
            {
                ans[q] = 1;
                break;
            }
        }
    }
}

void getData(int now, int fa, int val, int subtree)
{
    num[++cnt].w = val;
    num[cnt].v = now;
    bt[now] = subtree;
    for (auto& it : e[now])
    {
        auto [y, w] = it;
        if (y == fa || vis[y]) continue;
        getData(y, now, val + w, subtree);
    }
}

void init()
{
    cnt = siz = gravity = 0;
    mx = n;
}

void tree_div(int now, int fa)
{
    init();
    getSize(now, fa);
    getGravity(now, fa);

    vis[gravity] = 1;
    bt[gravity] = gravity;

    for (auto& it : e[gravity])
    {
        auto [y, w] = it;
        if (y == fa || vis[y]) continue;
        getData(y, gravity, w, y);
    }
    getAns(now, fa);
    for (auto& it : e[gravity])
    {
        auto [y, w] = it;
        if (y == fa || vis[y]) continue;
        tree_div(y, gravity);
    }
}


int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    for (int i = 1; i <= m; i ++)
    {
        int k;
        cin >> k;
        qs.push_back(k);
    }
    tree_div(1, 0);
    ans[0] = 1;
    for (auto it : qs)
    {
        if (ans[it]) 
            cout << "AYE" << '\n';
        else 
            cout << "NAY" << '\n';
    }
    return 0;
}