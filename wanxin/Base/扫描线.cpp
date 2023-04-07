#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 1E6 + 7;
int cnt = 0;

struct tn
{
    long long  l, r, m, len;
};

struct line
{
    long long m, l, r, h;

    bool operator<(line& a)
    {
        return h < a.h;
    }
};

tn tree[maxn << 2];
line le[maxn << 2];
int x[maxn << 2];
#define rhs now * 2 + 1
#define lhs now * 2
#define rrs tree[now].r
#define lls tree[now].l

void up(int now)
{
    int l = lls, r = rrs;
    if (tree[now].m)
        tree[now].len = x[r + 1] - x[l];
    else 
        tree[now].len = tree[lhs].len + tree[rhs].len;
}

void build(int now, long long l, long long r)
{
    rrs = r, lls = l;
    tree[now].len = 0;
	tree[now].m = 0;
    if (l == r)
        return ;
    int mid = (l + r) / 2;
    build(lhs, l, mid);
    build(rhs, mid + 1, r);
}

void change(int now, int nl, int nr, int num)
{
    int l = lls, r = rrs;
    if (nl >= x[r + 1] || nr <= x[l])
        return ;
    if (nl <= x[l] && nr >= x[r + 1])
    {
        tree[now].m += num;
        up(now);
        return ; 
    }
    change(lhs, nl, nr, num);
    change(rhs, nl, nr, num);
    up(now);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        le[++cnt] = {1, x1, x2, y1};
        x[cnt] = x1;
        le[++cnt] = {-1, x1, x2, y2};
        x[cnt] = x2;
    }
    sort(x + 1, x + cnt + 1);
    sort(le + 1, le + cnt + 1);
	int tot = unique(x + 1, x + cnt + 1) - x - 1;
    build(1, 1, tot - 1);
    long long ans = 0;
    for (int i = 1; i < cnt; i ++)
    {
        change(1, le[i].l, le[i].r, le[i].m);
        ans += tree[1].len * (le[i + 1].h - le[i].h);
    }
    cout << ans << '\n';
    return 0;
}