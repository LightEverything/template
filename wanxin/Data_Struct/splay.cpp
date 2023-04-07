#include <iostream>
#include <cmath>

using namespace std;
static const int maxn = 1E5 + 7;
int siz[maxn], val[maxn], ct[maxn];
int ch[maxn][2], fa[maxn];
int cnt = 0;
int a[maxn];
int lazy[maxn];

class Splay
{
public:
    int root;
    int* ord = a;

    void update(int x) 
    {
        if (x != 0)
            siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + ct[x];
    }

    bool get(int x)
    {
        return x == ch[fa[x]][1];
    }

    void clear(int x)
    {
        ch[x][0] = ch[x][1] = fa[x] = val[x] = ct[x] = siz[x] = 0;
    }

    void rot(int x)
    {
        int f = fa[x], g = fa[f], posx = get(x), posf = get(f);
        if (f == 0) return ;

        // x 子树
        if (lazy[x]) pushdown(x);
        if (lazy[f]) pushdown(f);

        ch[f][posx] = ch[x][posx^ 1];
        if (ch[x][posx ^ 1]) fa[ch[x][posx ^ 1]] = f;

        // x
        ch[x][posx ^ 1] = f;
        fa[f] = x;
        fa[x] = g;

        // g
        if (g) ch[g][f == ch[g][1]] = x;
        update(f);
        update(x);
    }

    void splay(int now, int up = 0)
    {
        while (fa[now] != up)
        {
            int f = fa[now], g = fa[f];
            // 折叠
            if (g && g != up)
                (ch[f][0] == now) ^ (ch[g][0] == f) ?  rot(now):rot(f);
            rot(now);
        }
        if (!up) root = now;
    }

    void insert(int num)
    {
        int now = root;
        while (now && val[now] != num && ch[now][num > val[now]])
            now = ch[now][num > val[now]];
        if (now && val[now] == num)
        {
            ct[now] ++;
            splay(now);
            return ;
        }

        val[++cnt] = num;
        ct[cnt] = siz[cnt] = 1;
        fa[cnt] = now;
        ch[cnt][0] = ch[cnt][1] = 0;
        ch[now][num > val[now]] = cnt;
        splay(cnt);
    }

    void del(int num)
    {
        if (!find(num)) return ;
        int now = root;
        if (ct[now] > 1)
        {
            ct[now] --;
            update(now);
            return ;
        }

        if (!ch[now][0] && !ch[now][1])
        {
            clear(now);
            root = 0;
            return ;
        }

        if (!ch[now][1])
        {
            root = ch[now][0];
            fa[root] = 0;
            clear(now);
            return ;
        }

        if (!ch[now][0])
        {
            root = ch[now][1];
            fa[root] = 0;
            clear(now);
            return ;
        }

        int x = p();
        fa[ch[now][1]] = x;
        ch[x][1] = ch[now][1];
        clear(now);
        update(root);
    }

    int find(int num)
    {
        int now = root;
        while (true)
        {
            if (lazy[now]) pushdown(now);
            if (now && num < val[now])
                now = ch[now][0];
            else if (now && num > val[now])
                now = ch[now][1];
            else 
            {
                if (now) splay(now);
                return now;
            }
        }
    }

    int kth(int k)
    {
        int now = root;
        while (now)
        {
            if (lazy[now]) pushdown(now);
            if (ch[now][0] && k <= siz[ch[now][0]])
                now = ch[now][0];
            else 
            {
                k -= ct[now] + siz[ch[now][0]];
                if (k <= 0)
                {
                    splay(now);
                    return now;
                }
                now = ch[now][1];
            }
        }
    }

    int lower_bound(int num)
    {
        int now = root;
        while (now)
        {
            if (val[now] >= num && val[ch[now][0]] < num)
            {
                splay(now);
                return now;
            }
            else if (val[now] < num)
                now = ch[now][1];
            else if (val[now] > num)
                now = ch[now][0];
        }
    }

    int upper_bound(int num)
    {
        int now = root;
        while (now)
        {
            if (val[now] > num && val[ch[now][0]] <= num)
            {
                splay(now);
                return now;
            }
            else if (val[now] <= num)
                now = ch[now][1];
            else if (val[now] > num)
                now = ch[now][0];
        }
    }

    int p()
    {
        int now = ch[root][0];
        if (!now) return now;
        while (ch[now][1]) now = ch[now][1];
        splay(now);
        return now;
    }

    int s()
    {
        int now = ch[root][1];
        if (!now) return now;
        while (ch[now][0]) now = ch[now][0];
        splay(now);
        return now;
    }

    void merge(Splay& tree2)
    {
        int& now = this->root;

        if (!tree2.root) 
            return ;
        if (!now) 
        {
            now = tree2.root;
            return ;
        }

        now = kth(siz[now]);
        ch[now][1] = tree2.root;
        fa[tree2.root] = now;
        // update(now);
    }

    void split(int k, Splay& tree2)
    {
        if (k == 0)
        {
            tree2.root = root;
            root = 0;
            return ;
        }

        int tmp = kth(k);
        tree2.root = ch[tmp][1];
        ch[tmp][1] = fa[tree2.root] = 0;
        root = tmp;
    }

    int rank(int num)
    {
        int ans = 0;
        int now = root;

        while (now)
        {
            if (num < val[now])
                now = ch[now][0];
            else 
            {
                ans += siz[ch[now][0]];
                if (num == val[now])
                {
                    splay(now);
                    return ans + 1;
                }
                ans += ct[now];
                now = ch[now][1];
            }
        }
        return 0;
    }

    int pre(int num)
    {
        insert(num);
        int tmp = p();
        del(num);
        return tmp;
    }

    int suffix(int num)
    {
        insert(num);
        int tmp = s();
        del(num);
        return tmp;
    }

    int build(int l, int r, int f)
    {
        if (l > r)
            return 0;
        int mid = (l + r) / 2;
        int now = ++cnt;
        fa[now] = f;
        val[now] = ord[mid];
        ch[now][0] = ch[now][1] = 0;
        siz[now] += 1;
        ct[now] = 1;
        ch[now][0] = build(l, mid - 1, now);
        ch[now][1] = build(mid + 1, r, now);
        update(now);
        return now;
    }

    void pushdown(int now)
    {
        lazy[ch[now][0]] ^= 1;
        lazy[ch[now][1]] ^= 1;
        swap(ch[now][0], ch[now][1]);
        lazy[now] = 0;
    }

    void reverse(int x, int y)
    {
        int l = x - 1, r = y + 1;
        l = kth(l), r = kth(r);
        splay(l, 0);
        splay(r, l);
        int pos = ch[root][1];
        pos = ch[pos][0];
        lazy[pos] ^= 1;
    }

    void dfs(int now)
    {
        if (lazy[now]) pushdown(now);
        if (ch[now][0]) dfs(ch[now][0]);
        if (val[now] != -1E9 + 7&& val[now] != 1E9 + 7)
            cout << val[now] << ' ';
        if (ch[now][1]) dfs(ch[now][1]);
    }
};


Splay sp;
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    a[1] = -1E9 + 7, a[n + 2] = 1E9 + 7;
    for (int i = 2; i <= n + 1; i ++)
        a[i] = i - 1;

    sp.root = sp.build(1, n + 2, 0);

    for (int i = 1; i <= m; i ++)
    {
        int x, y;
        cin >> x >> y;
        sp.reverse(x + 1, y + 1);
    }
    sp.dfs(sp.root);
}
