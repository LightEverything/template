#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

struct node
{
    int a, b, c, tot, res;

    bool operator!=(const node& n)
    {
        if (a == n.a && b == n.b && c == n.c)
            return false;
            // return true;
        return true;
    }
};

const int maxn = 2E5 + 7;
node tmp[maxn];
node a[maxn];
int tree[maxn];
int cnt = 0;
int k = 0;

bool cmpa(const node& x, const node& y)
{
    if (x.a != y.a)
        return x.a < y.a;
    else if (x.b != y.b)
        return x.b < y.b;
    else 
        return x.c < y.c;
}

bool cmpb(const node& x, const node& y)
{
    if (x.b != y.b)
        return x.b < y.b;
    else
        return x.c < y.c;
}

int lowbit(int x)
{
    return x & -x;
}

void add(int pos, int num)
{
    for (int i = pos; i <= k; i += lowbit(i)) tree[i] += num;

}

int query(int pos)
{
    int ans = 0;
    for (int i = pos; i ; i -= lowbit(i)) ans += tree[i];
    return ans;
}

void cdq(int l, int r)
{
    if (l == r)
        return ;
    int mid = (l + r) / 2;
    cdq(l, mid);
    cdq(mid + 1, r);

    sort(a + l, a + mid + 1, cmpb);
    sort(a + mid + 1, a + r + 1, cmpb);

    int nl = l;
    for (int i = mid + 1; i <= r; i ++)
    {
        while (a[nl].b <= a[i].b && nl <= mid)
        {
            add(a[nl].c, a[nl].tot);
            nl ++;
        }
        a[i].res += query(a[i].c); // 注意，所有的信息都应该一起转移
    }

    for (int i = l; i < nl; i ++)
        add(a[i].c, -a[i].tot);
}

int main(int argc, char** argv)
{
    int n;
    cin >> n >> k;
    
    for (int i = 1; i <= n; i ++)
        cin >> tmp[i].a >> tmp[i].b >> tmp[i].c;
    sort(tmp + 1, tmp + 1 + n, cmpa);

    int sum = 0;
    for (int i = 1; i <= n; i ++)
    {
        sum ++;
        if (tmp[i] != tmp[i + 1])
        {
            a[++cnt] = tmp[i];
            a[cnt].tot = sum;
            sum = 0;
        }
    }

    cdq(1, cnt);
    map<int, int> ans;
    for (int i = 1; i <= cnt; i ++) 
        ans[a[i].res + a[i].tot - 1] += a[i].tot;
    for (int i = 0; i < n; i ++)
        cout << ans[i] << '\n';
    return 0;
}