## 模板
----------------
### 数据结构
-----------------
#### 01字典树
```cpp
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int maxn = 1E5 + 7;
int trie[maxn << 4][2];
int ed[maxn << 4];
int a[maxn];
int cnt = 0;

inline void insert(int num)
{
    int p = 0;
    for (int i = 31; i >= 0; i --)
    {
        int tmp = ((num >> i) & 1);
        if (!trie[p][tmp]) trie[p][tmp] = ++ cnt;
        p = trie[p][tmp];
    }
    ed[p] ++;
}

inline int find(int num)
{
    int p = 0;
    int re = 0;
    for (int i = 31; i >= 0; i--)
    {
        int tmp = ((num >> i) & 1);
        if (trie[p][1 ^ tmp]) re += (1 << i), p = trie[p][1 ^ tmp];
        else  p = trie[p][tmp];
    }
    return re;
}

int main(int argc, char** argv)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        insert(a[i]);
    }
    
    int maxnn = 0;
    for (int i = 1; i <= n; i++)
        maxnn = max(maxnn, find(a[i]));
    cout << maxnn;
    return 0;
}
```

#### 优化版并查集
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E4 + 7;
int n = 0;
int fa[maxn];
int ranks[maxn]; // 秩

void init()
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        ranks[i] = 1;
    }
}

int find(int x)
{
    // 路径压缩
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void merge(int a, int b)
{
    // 秩合并
    int ffa = find(a), ffb = find(b);
    if (ffa == ffb) return ;
    if (ranks[ffa] < ranks[ffb]) swap(ffa, ffb);
    fa[ffb] = ffa;
    ranks[ffa] += ranks[ffb];
}

int main(int argc, char **argv)
{
    int m;
    cin >> n >> m;
    init();
    while (m--)
    {
        int op; // 题目 :操作1是合并，操作2是判断是否在同一个并查集内
        int a, b;
        cin >> op >> a >> b;
        if (op == 1)
            merge(a, b);
        else 
        {
            if (find(a) != find(b))
                cout << "N\n";
            else 
                cout << "Y\n";
        }
    }
    return 0;
}
```

#### 带权并查集
```cpp
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
```

#### 分块
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E5 + 7;
int a[maxn];
int n, m;
int add[maxn];
int st[maxn];
int ed[maxn];
int pos[maxn];
long long sum[maxn];
int block = 0;
int t = 0;

inline void init()
{
    block = sqrt(n);
    t = n / block + (n % block ? 1 : 0);

    for (int i = 1; i <= t; i++)
    {
        st[i] = (i - 1) * block + 1;
        ed[i] = i * block;
    }
    ed[t] = n;
    for (int i = 1; i <= n; i++)
        pos[i]=(i-1) / block + 1;
    for (int i = 1; i <= t; i++)
        for (int j = st[i]; j <= ed[i]; j++)
            sum[i] += a[j];
}

inline void change(int l, int r, int num)
{
    int p = pos[l], q = pos[r];
    if (p == q)
    {
        for (int i = l; i <= r; i++) a[i] += num;
        sum[p] += (r - l + 1) * num;
    }
    else 
    {
        for (int i = p + 1; i <= q - 1; i++) add[i] += num; 
        for (int i = l; i <= ed[p]; i++) a[i] += num;
        sum[p] += (ed[p] - l + 1) * num;
        for (int i = st[q]; i <= r; i++) a[i] += num;
        sum[q] += (r - st[q] + 1) * num;
    }
}


inline long long ask(int l, int r)
{
    int p = pos[l], q = pos[r];
    long long ans = 0;
    if (p == q)
    {
        for (int i = l; i <= r; i++) ans += a[i];
        ans += add[p] * (r - l + 1);
    }
    else 
    {
        for (int i = p + 1; i <= q - 1; i ++) ans += sum[i] + add[i] * (ed[i] - st[i] + 1);
        for (int i = l; i <= ed[p]; i ++) ans += a[i];
        ans += add[p] * (ed[p] - l + 1);
        for (int i = st[q]; i <= r; i ++) ans += a[i];
        ans += add[q] * (r - st[q] + 1);
    }
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    init();
    for (int i = 1; i <= m; i++)
    {
        char c;
        int r, l;
        cin >> c>> l >> r;
        if (c == 'Q')
            cout << ask(l, r) << '\n';
        else 
        {
            int num;
            cin >> num;
            change(l, r, num);
        }
    }
    
    return 0;
}
```

#### 简单字典树
```cpp

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
```

#### 莫队
```cpp

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int maxn = 1E6 + 7;
const int T = 2000;
int n, m;

int a[maxn];
int pos[maxn];
int cnt[maxn];
int out[maxn];

struct node
{
    int l, r, k;
};
node q[maxn];
int ans = 0;
inline bool cmp(node& a, node& b)
{
    if (pos[a.l] != pos[b.l] ) return a.l < b.l;
    else if (pos[a.l] & 1) return a.r > b.r;
    return a.r < b.r;
}

void del(int x)
{
    cnt[a[x]] --;
    if (cnt[a[x]] == 0) ans --;
}

void add(int x)
{
    cnt[a[x]] ++;
    if (cnt[a[x]] == 1) ans ++;
}

int main(int argc, char** argv)
{
    cin >> n;
    int block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[i] = (i - 1) / block + 1;
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].l >> q[i].r;
        q[i].k = i;
    }

    sort(q + 1, q + m + 1, cmp);
    int l = 1, r= 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        out[q[i].k] = ans;
    }
    for (int i = 1; i <= m; i++)
        cout << out[i] << '\n';
    return 0;
}
```

#### 树链剖分(宏定义版)
```cpp

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;
const long long maxn = 100000 + 7;
vector<long long > e[maxn << 1];
long long fa[maxn];
long long deep[maxn];
long long siz[maxn];
long long top[maxn];
long long son[maxn];
long long tree[maxn << 2];
long long cnt = 0;
long long to_id[maxn];
long long w[maxn];
long long old[maxn];
long long lazy[maxn << 2];
long long n, m;

void dfs(long long now, long long f)
{
    deep[now] = deep[f] + 1;
    siz[now] = 1;
    fa[now] = f;

    for (auto& y : e[now])
    {
        if (y == f) continue;
        fa[y] = now;
        dfs(y, now);
        siz[now] += siz[y];
        if (!son[now] || siz[son[now]] < siz[y])   son[now] = y;
    }
}


void dfs2(long long now, long long topn)
{
    to_id[now] = ++ cnt;
    w[cnt] = old[now];
    top[now] = topn;
    if (!son[now]) return ;
    dfs2(son[now], topn);

    for (auto& y : e[now])
    {
        if (y == fa[now]) continue;
        if (y != son[now]) 
            dfs2(y, y);
    }
}

long long lca(long long a, long long b)
{
    while (top[a] != top[b])
    {
        if (deep[top[a]] < deep[top[b]]) swap(a, b);
        a = fa[top[a]];
    }
    return deep[a] < deep[b] ? a : b;
}

void build(long long now, long long l, long long r)
{
    if (l == r)
    {
        tree[now] = w[l];
        return ;
    }
    long long mid = (l + r) / 2;
    build(now * 2, l, mid);
    build(now * 2 + 1, mid + 1, r);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

void update(long long now, long long l, long long r)
{
    lazy[now * 2] += lazy[now], lazy[now * 2 + 1] += lazy[now];
    long long mid = (l + r) / 2;
    tree[now * 2] += lazy[now] * (mid - l + 1), tree[now * 2 + 1] += lazy[now] * (r - mid);
    lazy[now] = 0;
}

void change(long long now, long long l, long long r, long long nl, long long nr, long long num)
{
    if (nl<= l && nr >= r)
    {
        lazy[now] += num;
        tree[now] += (r - l + 1) * num;
        return ;
    }
    if (lazy[now])
        update(now, l, r);
    long long mid = (l + r) / 2;
    if (nl <= mid) change(now * 2, l, mid, nl, nr, num);
    if (nr >= mid + 1) change(now * 2 + 1, mid + 1, r, nl, nr, num);
    tree[now] = tree[now * 2] + tree[now * 2 + 1];
}

long long ask(long long now, long long l, long long r, long long nl, long long nr)
{
    if (nl <= l && nr >= r)
    {
        return tree[now];
    }
    long long ans = 0;
    if (lazy[now])
        update(now, l, r);
    long long mid = (l + r) / 2;
    if (nl <= mid) ans += ask(now * 2, l ,mid, nl, nr);
    if (nr >= mid + 1) ans += ask(now * 2 + 1, mid + 1 ,r, nl, nr);
    return ans;
}

void treeChange(long long x, long long y, long long num)
{
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        change(1, 1, n, to_id[top[x]], to_id[x], num);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y]) swap(x, y);
    change(1, 1, n, to_id[x], to_id[y], num);
}

long long treeAsk(long long x, long long y)
{
    long long ans = 0;
    while (top[x] != top[y])
    {
        if (deep[top[x]] < deep[top[y]]) swap(x, y);
        ans += ask(1, 1, n, to_id[top[x]], to_id[x]);
        x = fa[top[x]];
    }
    if (deep[x] > deep[y]) swap(x, y);
    ans += ask(1, 1, n, to_id[x], to_id[y]);
    return ans;
}

inline void treeRootChange(long long x, long long num)
{
    change(1, 1, n, to_id[x], siz[x] + to_id[x] - 1, num);
}

inline long long treeRootAsk(long long x)
{
    return ask(1, 1, n, to_id[x], siz[x] + to_id[x]- 1);
}

int main(int argc, char** argv)
{
    cin >> n >> m;

    for (long long i = 1; i <= n; i++)
        cin >> old[i];
    for (long long i = 0; i < n- 1; i++)
    {
        long long a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    dfs(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    for (long long i = 0; i < m; i++)
    {
        long long op;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            long long x, a;
            cin >> x >> a;
            treeChange(x, x, a);
            break;
        }
        case 2:
        {
            long long x, y;
            cin >> x >> y;
            treeRootChange(x, y);
            break;
        }
        case 3:
        {
            long long x;
            cin >> x;
            cout << treeAsk(1, x) << '\n';
            break;
        }
        }
    }
    return 0;
}
```

#### 树状数组(带简单离散化)
```cpp

#include <iostream>
#include <cstring>
#include <map>

using namespace std;

const int maxn = 2E5 + 7;
int n;
int tree[maxn];
int re[maxn];
pair<int, int> a[maxn];

inline int lowbit(int x)
{
    return x & -x;
}

inline int sum(int num)
{
    int ans = 0;
    for (int i = num; i ; i -= lowbit(i)) ans += tree[i];
    return ans;
}
inline void add(int pos , int num) 
{ 
    for (int i = pos; i <= n; i += lowbit(i)) tree[i] += num;
}

int main(int argc, char** argv)
{
    while (cin >> n)
    {
        // 初始化
        memset(tree, 0, sizeof tree);
        for (int i  =1; i <= n; i++)
        {
            cin >> a[i].first >> a[i].second;
            ++a[i].first;
            add(i, 1);

        }
        
        for (int i = n; i; i--)
        {
            int l = 1, r =n;
            // 普通二分
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (sum(mid) >= a[i].first)  r = mid;
                else l = mid + 1;            
            }
            re[l] = a[i].second;
            add(l, -1);
        }
        
        for (int i = 1; i <= n; i++)
            cout << re[i] << ' ';
        cout << '\n';
    }
    return 0;
}
```

#### 普通线段树
```cpp

#include <iostream>

const int maxn = 1E5 + 7;

#define rhs now * 2 + 1
#define lhs now * 2
#define lls tree[now].l
#define rrs tree[now].r

using namespace std;
struct node 
{
    long long l, r, x;
};
node tree[maxn << 2];
long long lazy[maxn << 2];
int a[maxn];


inline void up(int now) { tree[now].x = tree[lhs].x + tree[rhs].x; }

void build(int now, int l, int r)
{
    lls = l, rrs = r;
    if (l == r)
    {
        tree[now].x = a[l];
        return ;
    }

    int mid = (lls + rrs) / 2;
    build(lhs, l, mid);
    build(rhs, mid + 1, r);
    up(now);
}

void update(int now)
{
    int mid = (lls + rrs) / 2;
    tree[lhs].x += lazy[now] * (mid - lls+ 1), tree[rhs].x += lazy[now] * (rrs - mid);
    lazy[lhs] += lazy[now], lazy[rhs] += lazy[now];
    lazy[now] = 0;
}

void change(int now, int nl, int nr, int num)
{
    if (nl <= tree[now].l && nr >= tree[now].r)
    {
        lazy[now] += num;
        tree[now].x += num * (tree[now].r - tree[now].l + 1);
        return ;
    }
    if (lazy[now]) update(now);
    int mid = (lls + rrs) / 2;
    if (nl <= mid) change(lhs, nl, nr, num);
    if (nr >= mid + 1) change(rhs, nl, nr, num);
    up(now);
}

long long answer(int now, int nl, int nr)
{
    if (nl <= lls && nr >= rrs)
    {
        return tree[now].x;
    }
    if (lazy[now])  update(now);
    long long ans = 0;
    int mid = (lls + rrs) / 2;
    if (nl <= mid) ans += answer(lhs, nl, nr);
    if (nr >= mid + 1) ans += answer(rhs, nl, nr);
    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++)
        cin >> *(a + i);
        
    build(1, 1, n);

    while (m --)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, y, k;
            cin >> x >> y >> k;
            change(1, x, y, k);
        }
        else 
        {
            int x, y;
            cin >> x >> y;
            cout << answer(1, x, y) << '\n';
        }
    }
    return 0;
}
```

####  种类并查集
```cpp

#include <iostream>
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 5E4 + 7;
int fa[maxn * 3];

int find(int a)
{
    return fa[a] == a ? a : (fa[a] = find(fa[a]));
}

int main(int argc, char** argv)
{
    int n, m;
    int ans = 0;
    cin >> n >> m;

    for (int i =1; i <= 3 * n; i++)
        fa[i] = i;

    for (int i = 0; i < m; i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        
        if (l > n || r > n || (op == 2 && l == r))
        {
            ans ++;
        }
        else 
        {
            if (op == 1)
            {
                if (find(l) == find(r + n) || find(r) == find(l + n))  ans++;
                else 
                {
                    fa[find(l)] = find(r);
                    fa[find(l + n)] = find(r + n);
                    fa[find(l + 2 * n)] = find(r + 2 * n);
                }
            }
            else 
            {
                if (find(r + n) == find(l) || find(l) == find(r)) ans++;
                else 
                {
                    fa[find(l + n)] = find(r);
                    fa[find(l + 2 * n)] = find(r + n);
                    fa[find(l)] = find(r + 2 * n);
                }
            }
        }
    }

    cout << ans;
    return 0;
}
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 5E4 + 7;
int fa[maxn * 3];

int find(int a)
{
    return fa[a] == a ? a : (fa[a] = find(fa[a]));
}

int main(int argc, char** argv)
{
    int n, m;
    int ans = 0;
    cin >> n >> m;

    for (int i =1; i <= 3 * n; i++)
        fa[i] = i;

    for (int i = 0; i < m; i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        
        if (l > n || r > n || (op == 2 && l == r))
        {
            ans ++;
        }
        else 
        {
            if (op == 1)
            {
                if (find(l) == find(r + n) || find(r) == find(l + n))  ans++;
                else 
                {
                    fa[find(l)] = find(r);
                    fa[find(l + n)] = find(r + n);
                    fa[find(l + 2 * n)] = find(r + 2 * n);
                }
            }
            else 
            {
                if (find(r + n) == find(l) || find(l) == find(r)) ans++;
                else 
                {
                    fa[find(l + n)] = find(r);
                    fa[find(l + 2 * n)] = find(r + n);
                    fa[find(l)] = find(r + 2 * n);
                }
            }
        }
    }

    cout << ans;
    return 0;
}
```

#### lca(欧拉序列 + rmq)
```cpp

#define quick

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>

const int maxn = 5E5 + 7;
using namespace std;
vector<int> ch[maxn]; // 邻接表
int cnt = 0;
int root = 0, n = 0, s = 0;
int num = 0;
int rmq[(maxn << 1)][31];
int oula[(maxn << 1)];
int first[(maxn << 1)];
int to_ei[(maxn << 1)];

void rmqInit()
{
    for (int i = 1; i <= cnt; i++)
        rmq[i][0] = oula[i];
    int m = log2(cnt);
    for (int j = 1; j <= m; j++)
    {
        int t = cnt - (1 << j) + 1;
        for (int i = 1; i <= t; i++)
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j-1]);
    }
}

int rmqFind(int l, int r)
{
    int m = log2(r -l + 1);
    return min(rmq[l][m], rmq[r - (1 << m) + 1][m]);
}

void dfs(int now, int ffa)
{
    int tmp = ++num;
    oula[++cnt] = tmp;
    to_ei[tmp] = now;
    first[now] = cnt;
    for (auto item : ch[now])
    {
        if (item == ffa) continue;
        dfs(item, now);
        oula[++cnt] = tmp;
    }
}

int lca(int a, int b)
{
    if (first[a] > first[b]) swap(a, b);
    return to_ei[rmqFind(first[a], first[b])];
}

int main(int argc, char** argv)
{
#ifdef quick
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    cin >> n >> s >> root;
    for (int i = 0 ; i < n  -1; i++)
    {
        int tfa, tch;
        cin >> tfa >> tch;
        ch[tfa].push_back(tch);
        ch[tch].push_back(tfa);
    }
    dfs(root, 0);
    rmqInit();

    for (int i = 0 ;i < s; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << lca(l, r) << '\n';
    }

    return 0;
}
```

#### rmq(st)
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 1E5 + 7;
int n, m;
int a[maxn] = {0};
int rmq[maxn][31] = {0};

void rmqInit()
{
    for (int i = 1; i <= n; i++)
        rmq[i][0] = a[i];
    int m = log2(n);
    for (int j = 1; j <= m; j++)
    {
        int t = n - (1 << j) + 1;
        for (int i = 1; i <= t; i++)
            rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j-1]);
    }
}

int rmqFind(int l, int r)
{
    int m = log2(r -l + 1);
    return max(rmq[l][m], rmq[r - (1 << m) + 1][m]);
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
    rmqInit();
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << rmqFind(l, r) << '\n';
    }
    return 0;
}
```

#### splay
```cpp
#include <iostream>
#include <climits>
#include <cmath>
#include <cstdio>

using namespace std;
const int maxn = 1E5 + 7;
int minn = 0;
int delta = 0;

struct node
{
    int s[2], p, v;
    int size;

    void init(int v, int p)
    {
        s[1] = s[0] = 0;
        this->v = v;
        this->p = p;
        this->size = 1;
    }
};

int root, idx;
int total = 0;
node tree[maxn];

inline void pushUp(int now)
{
    tree[now].size = tree[tree[now].s[0]].size + tree[tree[now].s[1]].size + 1;
}

inline void rotate(int x)
{
    int y = tree[x].p, z = tree[y].p;
    int k = tree[y].s[1] == x;
    tree[z].s[tree[z].s[1] == y] = x, tree[x].p =  z;
    tree[y].s[k] = tree[x].s[k ^ 1], tree[tree[x].s[k ^ 1]].p = y;
    tree[x].s[k ^ 1] = y, tree[y].p = x;
    pushUp(y), pushUp(x);
}   

inline void splay(int x, int k)
{
    while (tree[x].p != k)
    {
        int y = tree[x].p, z = tree[y].p;
        if (z != k)
        {
            if ((tree[y].s[1] == x) ^ (tree[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}

inline int insert(int v)
{
    int u = root, p = 0;
    while (u) p = u, u = tree[u].s[v > tree[u].v];
    u = ++idx;
    if (p) tree[p].s[v > tree[p].v] = u;
    tree[u].init(v, p);
    splay(u, 0);
    return u;
}

int get(int v)
{
    int u = root, res =0 ;
    while (u)
    {
        if (tree[u].v >= v) res = u, u = tree[u].s[0];
        else u = tree[u].s[1];
    }
    return res;
}

int get_k(int k)
{
    int u = root;
    while (u)
    {
        if (tree[tree[u].s[0]].size >= k ) u = tree[u].s[0];
        else if (tree[tree[u].s[0]].size + 1 == k) return tree[u].v;
        else k -= tree[tree[u].s[0]].size + 1, u = tree[u].s[1];
    }
    return -1;
}


int main(int argc ,char** argv)
{
    int n;
    cin >> n >> minn;
    int L = insert(INT_MIN), R = insert(INT_MAX);

    for (int i = 1; i <= n; i++)
    {
        char op;
        int num;
        cin >> op >> num;
        if (op == 'I')
        {
            if (num >= minn)
            {
                total ++;
                insert(num - delta);
            }
        }
        else if (op == 'S')
        {
            delta -= num;
            R = get(minn - delta);
            splay(R, 0), splay(L, R);
            tree[L].s[1] = 0;
            pushUp(L), pushUp(R);
        }
        else if (op == 'F')
        {
            if (tree[root].size - 2 < num) cout << - 1 << '\n';
            else cout << get_k(tree[root].size - num) + delta << '\n';
        }
        else 
        {
            delta += num;
        }
    }
    cout << total - (tree[root].size - 2) << '\n';
    return 0;
}
```

---------------------------
### 字符串
----------------------
#### kmp
```cpp

#include <iostream>
#include <string>

using namespace std;
string str1, str2;
const int maxn = 1E6 + 7;
int nexta[maxn];

void  initkmp()
{
    int size2 = str2.size();
    int cnt = 0;
    nexta[0] = -1;

    for (int i = 2; i <= size2; i++)
    {
        while (cnt && str2[i - 1] != str2[cnt])
            cnt = nexta[cnt];
        if (str2[i - 1] == str2[cnt])
            cnt ++;
        nexta[i] = cnt;
    }
    return ;
}

int main(int argc ,char** argv)
{
    cin >> str1 >> str2;

    int j = 0, i = 0;
    initkmp();

    for (int i  = 0; i < str1.size(); i++)
    {
        while (j && str1[i] != str2[j])
            j = nexta[j];
        if (str1[i] == str2[j])
            j ++;
        if (j == str2.size())   
        {
            cout << i - j  + 2 << '\n';
            j = nexta[j];
        }
    }

    for (int i = 1; i <= str2.size(); i++)
        cout << nexta[i] << ' ';
    return 0;
}
```

-------------------------
### 图论
------------------------
####  2-SAT模板
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=2500000;
const int M=3000000;
int n,m,fen;
int head[N],ver[M],Next[M];
int low[N],dfn[N],stacks[N],c[N],vis[N],tot,num,cnt,top;
vector<int> scc[N];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	stacks[++top]=x; vis[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnt++;
		int y;
		do{
			y=stacks[top--];
			vis[y]=0; c[y]=cnt;
			scc[cnt].pb(y);
		}while(x!=y);
	}
}

bool solve()
{
	for(int i=1;i<=n*2;i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(c[i]==c[i+fen]) return false;
	}
	return  true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	fen=n;
	for(int k=1;k<=m;k++){
		int i,a,j,b;
		cin>>i>>a>>j>>b;
		if(a&&b){
			add(i+fen,j); add(j+fen,i);
		}else if(!a&&b){
			add(i,j); add(j+fen,i+fen);
		}else if(a&&!b){
			add(i+fen,j+fen); add(j,i);
		}else if(!a&&!b){
			add(i,j+fen); add(j,i+fen);
		}
	}
	if(solve()){
		cout<<"POSSIBLE"<<endl;
		for(int i=1;i<=n;i++){
			if(c[i]<c[i+fen]) cout<<"1"<<" ";
			else cout<<"0"<<" ";
		}
	}else {
		cout<<"IMPOSSIBLE";
	}	
	return 0;
}
```

#### bellman_ford
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
const int inf=0x3f3f3f3f;
#define ll long long 

ll cube(ll x)
{
	return x*x*x;
}

ll d[501];
ll nd_cost[501];

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int nd,u,v,edg,t=0,kase=0;
	while(cin>>nd){
		kase++;
		for(int i=1;i<=nd;i++) cin>>nd_cost[i];
		vector<pair<int,int> > vec;
		cin>>edg;
		for(int i=1;i<=edg;i++){ 
			cin>>u>>v;
			vec.pb(make_pair(u,v));
		}
		memset(d,0x3f,sizeof(d));
		d[1]=0;
		for(int i=1;i<=nd*2;i++){
			bool isbreak= true;
			for(int j=0;j<edg;j++){
				int u=vec[j].first,v=vec[j].second;
				int w=cube(nd_cost[v]-nd_cost[u]);
				if(d[u]+w<d[v]){
					isbreak=false;
					if(i>=nd) d[v]=-inf;
					else d[v]=d[u]+w;
				}
			}
			if(isbreak) break;
		}
		cout<<"Set #"<<kase<<endl;
		cin>>edg;
		while(edg--){
			int v;
			cin>>v;
			if(d[v]<3||d[v]>100000) cout<<"?"<<endl;
			else cout<<d[v]<<endl;
		}
	}
}
```

#### Dijkstra算法板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define pii pair<int,int>
#define mk(a,b) make_pair(a,b)
#define mem(a,x) memset(a,x,sizeof(a))
const int N=10010;
const int M=100010;
int head[N],ver[M],edge[M],Next[M];
int vis[N],d[N];
int n,m,tot;

priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > > q;

void add(int x,int y,int w)
{
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
    edge[tot]=w;
}

void dijkstra( int term)
{
    mem(d,0x3f);
    mem(vis,0);
    d[term]=0;
    q.push(mk(0,term));
    while(!q.empty()){
        int x=q.top().second;q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i;i=Next[i]){
            int y=ver[i],z=edge[i];
            if(d[y]>d[x]+z){
                d[y]=d[x]+z;
                q.push(mk(d[y],y));
            }
        }
    }
}

```

#### floyd求最短路
```cpp
// C++ Version
memset(f,0x3f,sizeof(f));
for(int i=1;i<=n;i++) f[i][i]=0;
for (k = 1; k <= n; k++) {
  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
    }
  }
}
```

#### Kruskal算法求最小生成树板子
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define endl "\n"
#define pb emplace_back

int n,m;				//number of vertex,edge
const int N=1001; 		//图的点数
const int M=10010;     	//图的边数
struct _edge{
    int u,v,w;
    bool operator<(const _edge & t) const
    {
        return w<t.w;
    }
}edge[M];

int fa[N],sz[N];

int get(int x){
    return x==fa[x]?x:fa[x]=get(fa[x]);
}

bool merge(int x,int y)
{
    x=get(x),y=get(y);
    if(x!=y){                       //它这个合并是带查询是否在同一个集合里的功能的
        if(sz[x]<sz[y])swap(x,y);
        fa[y]=x;sz[x]+=sz[y];
        return 1;
    }
    return 0;
}

void init( void )
{
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;		//并查集初始化;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>edge[i].u>>edge[i].v>>edge[i].w;
    //按边权排序
    sort(edge+1,edge+1+m);
	//并查集初始化
    init();
    //求最小生成树
    int ans=0;
    for(int i=1;i<=m;i++){
    	int x=edge[i].u,y=edge[i].v,w=edge[i].w;
    	if(merge(x,y)) ans+=w;
    }
    cout<<ans<<endl;
}   
```

#### LCA倍增算法
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));
typedef long long ll;
const int N=1005;
const int M=10005;
int f[N][20],d[N],dist[N];
int head[N],ver[M],edge[M],Next[M];
int n,m,tot,t;

void add(int x,int y,int z)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}

void bfs()		//预处理
{
	queue<int> q;
	q.push(1); d[1]=1;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(d[y]) continue;
			d[y]=d[x]+1;
			dist[y]=dist[x]+edge[i];
			f[y][0]=x;
			for(int j=1;j<=t;j++){
				f[y][j]=f[f[y][j-1]][j-1];
			}
			q.push(y);
		}
	}
}

int lca(int x,int y)
{
	//回答一个询问
	if(d[x]>d[y]) swap(x,y); //要求y比x深
	for(int i=t;i>=0;i--){
		if(d[f[y][i]]>=d[x]) y=f[y][i];
	}
	//此时y与x的深度相同
	if(x==y) return x;
	for(int i=t;i>=0;i--){
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}

void init()
{
	mem(f,0);
	mem(d,0);
	mem(dist,0);
	mem(head,0);
	tot=1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase;
	cin>>kase;
	while(kase--){
		cin>>n>>m;
		t=(int)(log(n)/log(2))+1;
		init();
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u,v,w);
			add(v,u,w);
		}
		bfs();
		//回答问题
		int q;
		cin>>q;
		for(int i=1;i<=q;i++){
			int x,y;
			cin>>x>>y;
			cout<<(dist[x]+dist[y]-2*dist[lca(x,y)])<<endl;
		}
	}
	return 0;
}
```

#### LCA求最小瓶颈路
```cpp
// LCA
const int maxn = 2e5 + 5;
int up[maxn][23], maxx[maxn][23];
int deep[maxn], dis[maxn];
int cnt, head[maxn];
int n, m, q;
struct node {  //  存树
    int to, next, w;
}e[maxn<<1];
void init() {
    Fill(head,-1); Fill(dis,0);
    Fill(up,0);  Fill(deep,0);
    cnt = 0;  Fill(maxx, -1);
}
void add(int u, int v, int w) {
    e[cnt] = node{v, head[u], w};
    head[u] = cnt++;
}

void dfs(int u,int fa,int d) {
    deep[u] = d + 1;
    for(int i = 1 ; i < 20 ; i ++) {
        up[u][i] = up[up[u][i-1]][i-1];
        maxx[u][i] = max(maxx[up[u][i-1]][i-1], maxx[u][i-1]);
    }
    for(int i = head[u] ; ~i ; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dis[to] = dis[u] + e[i].w;
        up[to][0] = u;
        maxx[to][0] = e[i].w;
        dfs(to, u, d+1);
    }
}

int LCA_BZ(int u,int v) {
    int mx = 0;
    if(deep[u] < deep[v]) swap(u,v);
    int k = deep[u] - deep[v];
    for(int i = 0 ; i < 20 ; i ++) {
        if((1<<i) & k) {
            mx = max(mx, maxx[u][i]);
            u = up[u][i];
        }
    }
    if(u != v) {
        for(int i = 19 ; i >= 0 ; i --) {
            if(up[u][i] != up[v][i]) {
                mx = max(mx, max(maxx[u][i], maxx[v][i]));
                u = up[u][i];
                v = up[v][i];
            }
        }
        mx = max(mx, max(maxx[u][0], maxx[v][0]));
        u = up[u][0];
    }
    return mx;
    //return u;
}
```

#### spfa板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));
#define pii pair<int,int>
const int INF=0x3f3f3f3f;
const int N=10000;
const int M=100000;
int head[N],ver[M],edge[M],Next[M];
int d[N],cnt[N],vis[N];
int n,m,tot=0;
queue<int> q;

void add(int x,int y,int w)
{
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
    edge[tot]=w;
}

bool spfa( int s )
{
  mem(d,0x3f);
  mem(vis,0);
  d[s]=0; vis[s]=1;
  q.push(s);
  while(!q.empty()){
    int x=q.front(); q.pop();
    vis[x]=0;
    for(int i=head[x];i;i=Next[i]){
      int y=ver[i],w=edge[i];
      if(d[y]>d[x]+w){
        d[y]=d[x]+w;
        cnt[y]=cnt[x]+1;    //记录最短路径经过的边数
        if(cnt[y]>=n) return false;     //经过了负环
        if(!vis[y]) q.push(y),vis[y]=1;
      }
    }
  }
  return true;
}
```

#### tarjan算法与割边
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100005;
int head[N],ver[N*2],Next[N*2];
int dfn[N],low[N],n,m,tot,num;
int bridge[N*2];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x,int in_edge)
{
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]){
				bridge[i]=1;
				bridge[i^1]=1;
			}
		}else {
			if(i!=(in_edge^1)){
				low[x]=min(low[x],low[y]);
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	tot=1;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i,0);
	}
	for(int i=2;i<=tot;i+=2){
		if(bridge[i]) cout<<ver[i]<<" "<<ver[i^1]<<endl;
	}
	return 0;
}
```
#### tarjan算法与割点
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100005;
int n,m;
int head[N],ver[2*N],Next[2*N];
int dfn[N],low[N],num,tot,root;
int cut[N];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	int cnt=0;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				cnt++;
				if(x!=root||cnt>1) cut[x]=1;
			}
		}else {
			low[x]=min(low[x],dfn[y]);
		}
	}

}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	tot=1;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(dfn[i]) root=i,tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(cut[i]) cout<<i<<" ";
	}
	return 0;
}
```
---------------
### 数学
---------------
#### 逆序对
```cpp
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 5E5 + 7;
int n;
int a[maxn];
int sorta[maxn];
int tree[maxn];
int cnt = 0;
unordered_map<int , int> mp;
long long ans = 0;

inline int lowbit(int x)
{
    return x & -x;
}

void insert(int x, int num)
{
    for (int i = x; i <= n; i += lowbit(i)) tree[i] += num;
}

int getsum(int x)
{
    int tmp = 0;
    for (int i = x; i ; i -= lowbit(i)) tmp += tree[i];
    return tmp;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sorta[i] = a[i];
    }

    sort(sorta + 1, sorta + n + 1);

    // 离散化
    for (int i = 1; i <= n; i++)
    {
        if (!mp[sorta[i]]) mp[sorta[i]] = ++cnt;
    }

    for (int i = 1; i <= n; i++)
    {   
        int x = mp[a[i]];
        insert(x, 1);
        ans += i - getsum(x);
    }

    cout << ans;
    return 0;
}

/**
 * @brief 非map形式的逆序对
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int tree[500010],ranks[500010],n; // rank与a使用同一个计数器
long long ans; 
struct point
{
    int num,val;
}a[500010];
inline bool cmp(point q,point w)
{
    if(q.val==w.val)
        return q.num<w.num;
    return q.val<w.val;
}
inline void insert(int p,int d)
{
    for(;p<=n;p+=p&-p)
        tree[p]+=d; 
}
inline int query(int p)
{
    int sum=0;
    for(;p;p-=p&-p)
        sum+=tree[p];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].val),a[i].num=i;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
        ranks[a[i].num]=i;
    for(int i=1;i<=n;i++)
    {
        insert(ranks[i],1);
        ans+=i-query(ranks[i]);
    }
    printf("%lld",ans);
    return 0;
} 
 * 
 */
```

#### 边带权并查集板子
```cpp
//边带权并查集的板子

const int MS=10010;//size of array
struct _edge{
    int u,v,w;
    bool operator<(const _edge & t) const
    {
        return w<t.w;
    }
}edge[MS];

int fa[MS],sz[MS];

int findf(int u){
    return u==fa[u]?u:fa[u]=findf(fa[u]);
}

bool uni(int u,int v)
{
    u=findf(u),v=findf(v);
    if(u!=v){                       //它这个合并是带查询是否在同一个集合里的功能的
        if(sz[u]<sz[v])swap(u,v);
        fa[v]=u;sz[u]+=sz[v];
        return 1;
    }
    return 0;
}

int main()
{
    int n,m;//number of vertex,edge
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
    for(int i=0;i<m;i++)cin>>edge[i].u>>edge[i].v>>edge[i].w;
    sort(edge,edge+m);
    int ans=0;//total weight
    for(int i=0;i<m;i++)
    {
        int u=edge[i].u,v=edge[i].v,w=edge[i].w;
        if(uni(u,v))ans+=w;
    }
    printf("%d\n",ans);
}   
```
#### 边双连通分量
```cpp
struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[maxm];
int n,m,stamp,dfn[maxn],low[maxn],bccno[maxn],bcc_cnt;
vector<int> vec[maxn],bcc[maxn];
bool g[maxn][maxn],isbridge[maxm];

void tarjan(int index,int fa)
{
    int tmp;
    dfn[index]=low[index]=++stamp;
    for(int i=0;i<vec[index].size();i++)
    {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp])
        {
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>dfn[index])
                isbridge[vec[index][i]]=isbridge[vec[index][i]^1]=1;
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa)
        {
            low[index]=min(low[index], dfn[tmp]);
        }
    }
}

void dfs(int index)
{
    dfn[index]=1;
    bccno[index]=bcc_cnt;
    for(int i=0;i<vec[index].size();i++)
    {
        int tmp=vec[index][i];
        if(isbridge[tmp])
            continue;
        if(!dfn[e[tmp].v])
        {
            dfs(e[tmp].v);
        }
    }
}

void find_ebcc(){
    bcc_cnt=stamp=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(isbridge,0,sizeof(isbridge));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i, -1);
    memset(dfn,0,sizeof(dfn));
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
        {
            bcc_cnt++;
            dfs(i);
        }
    }               
}
```
#### 差分约束系统板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int inf=0x3f3f3f3f,N=7000,M=100000;
int head[N],ver[M],Next[M],edge[M],vis[N],cnt[N],dist[N];
int n,m,tot;

void add(int x,int y,int w)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w;
}

bool spfa(int s)
{
	memset(dist,0x3f,sizeof(dist));
	memset(cnt,0,sizeof(cnt));
	queue<int> q; q.push(s);
	vis[s]=1; dist[s]=0; cnt[s]++;
	while(!q.empty()){
		int x=q.front(); q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(dist[y]>dist[x]+edge[i]){
				dist[y]=dist[x]+edge[i];
				cnt[y]++;
				if(cnt[y]>=n+1) return false;   //这里是n+1,因为多加了一个超级源点
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return true;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		add(0,i,0);
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(v,u,w);
	}
	if(!spfa(0)) {
		cout<<"NO"<<endl;
		return 0;
	}
	int mins=inf;
	for(int i=1;i<=n;i++) mins=min(mins,dist[i]);
	for(int i=1;i<=n;i++){
		cout<<dist[i]-mins<<" ";
	}
	return 0;
}
```
#### 点双连通分量
```cpp
struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[maxm];
int n,m,stamp,dfn[maxn],low[maxn],iscut[maxn],bccno[maxn];
int scnt,stack[maxm],bcc_cnt;
vector<int> vec[maxn],bcc[maxn];

void tarjan(int index,int fa)
{
    int child=0,tmp;
    dfn[index]=low[index]=++stamp;
    for(int i=0;i<vec[index].size();i++)
    {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp])
        {
            stack[++scnt]=vec[index][i],child++;
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>=dfn[index])
            {
                iscut[index]=1;
                bcc[++bcc_cnt].clear();
                while(1)
                {
                    int num=stack[scnt--];
                    if(bccno[e[num].u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u]=bcc_cnt;
                    }
                    if(bccno[e[num].v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v]=bcc_cnt;
                    }
                    if(e[num].u==index && e[num].v==tmp)
                        break;
                }
            }
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa)
        {
            stack[++scnt]=vec[index][i];
            low[index]=min(low[index], dfn[tmp]);
        }
    }
    if(fa<0 && child==1)
        iscut[index]=0;
}

void find_bcc()
{
    // 割顶的bccno值无意义 
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
}
```
#### 二分图判定
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

int v;
vector<int> ve[350];
int color[340];

bool dfs(int cur,int c)
{
	color[cur]=c;
	for(auto a : ve[cur]){
		if(color[a]){
			if(color[a]==c) return false;
		}else {
			if(!dfs(a,-c)) return false;
		}
	}
	return true;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	while(cin>>v&&v!=0){
		for(int i=1;i<=v;i++){
			ve[i].clear();
		}
		while(1){
			int u,v;
			cin>>u>>v;
			if(u+v==0) break;
			ve[u].pb(v);
			ve[v].pb(u);
		}
		memset(color,0,sizeof(color));
		int ok=1;
		for(int i=1;i<=v;i++){
			if(color[i]==0){
				if(!dfs(i,1)) {
					ok=0;
					break;
				}
			}
		}
		if(ok) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```
#### 二分图匹配匈牙利算法板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=1000;
const int M=10000;
int match[N],vis[N],cnt,n;
vector<int> ve[N];

bool dfs(int u)
{
	for(auto v: ve[u]){
		if(vis[v]==cnt) continue;
		vis[v]=cnt;
		if(!match[v]||dfs(match[v])){	
			match[v]=u;
			return true;
		}
	}
	return false;
}

int solve()
{
	int ans=0;
	for(int i=1;i<=n;i++){
		cnt=i;
		if(dfs(i)) ans++;
	}
	return ans;
}

void init()
{
	memset(match,0,sizeof(match));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++) ve[i].clear();
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	return 0;
}
```
#### 费用流Dinic
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int inf=0x3f3f3f3f,N=5e3+5,M=1e5+5;
int head[N],ver[M],Next[M],edge[M],now[N],cost[M],dist[N],vis[N];
int n,m,s,t,tot,maxflow,ret;

void add(int x,int y,int w,int c)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w; cost[tot]=c;
	ver[++tot]=x; Next[tot]=head[y]; head[y]=tot; edge[tot]=0; cost[tot]=-c;
}

bool spfa()
{
	memset(dist,0x3f,sizeof(dist));
	queue<int> q; q.push(s);
	dist[s]=0; vis[s]=1;
	now[s]=head[s];
	while(!q.empty()){
		int x=q.front(); q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(edge[i]&&dist[y]>dist[x]+cost[i]){
				dist[y]=dist[x]+cost[i];
				now[y]=head[y];
				if(!vis[y]) q.push(y),vis[y]=1;
			}
		}
	}
	return dist[t]!=inf;
}

int dinic(int x,int flow)
{
	if(x==t) return flow;
	vis[x]=1; 
	int rest=flow,k;
	for(int i=now[x];i&&rest;i=Next[i]){
		int y=ver[i];
		now[x]=i;
		if(!vis[y]&&edge[i]&&dist[y]==dist[x]+cost[i]){
			k=dinic(y,min(rest,edge[i]));
			if(k){
				ret+=k*cost[i];
				edge[i]-=k;
				edge[i^1]+=k;
				rest-=k;
			}
		}
	}
	vis[x]=0;
	return flow-rest;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m>>s>>t;
	tot=1; maxflow=0; ret=0;
	for(int i=1;i<=m;i++){
		int u,v,w,c;
		cin>>u>>v>>w>>c;
		add(u,v,w,c);
	}
	int flow=0;
	maxflow=0; ret=0;
	while(spfa()){
		while(flow=dinic(s,inf)) maxflow+=flow;
	}
	cout<<maxflow<<" "<<ret<<endl;
	return 0;
}
```
#### 两次DFS求树的直径_不适用于负权图
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define endl "\n"
#define mem(a,x) memset(a,x,sizeof(a))
typedef long long ll;

const int N=1000;
const int M=10000;
int head[N],ver[M],Next[M],edge[M];
int dist[N];
int n,m,p,tot;

void add(int x,int y,int w)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=w;
}

void dfs(int x, int fa) {
	for(int i=head[x];i;i=Next[i]){
  		int y=ver[i];
  		if(y==fa) continue;
  		dist[y]=dist[x]+edge[i];
  		if(dist[y]>dist[p]) p=y;
  		dfs(y,x);
    }
}

void init()
{
	mem(head,0);
	mem(dist,0);
	p=1;
	tot=1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase=0;
	cin>>kase;
	while(kase--){
		cin>>n>>m;
		init();
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u,v,w);
			add(v,u,w);
		}
		p=1;
		dfs(1,0);
		mem(dist,0); 
		dfs(p,0);
		cout<<dist[p]<<endl;
	}
	return 0;
}
```
#### 欧拉回路
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=55;
const int M=1005;
int deg[N],vis[N];
int g[N][N];
int n,m;

void dfs(int x )
{
	for(int i=1;i<=n;i++){
		if(g[x][i]){
			g[x][i]--; g[i][x]--;
			//cout<<x<<" "<<i<<endl;
			dfs(i);
			cout<<i<<" "<<x<<endl;
		}
	}
}

void dfs_2(int x,int fa)
{
	vis[x]=1;
	for(int i;i<=n;i++){
		if(i!=fa&&!vis[i]&&g[x][i]){
			dfs_2(i,x);
		}
	}
}

void init()
{
	memset(deg,0,sizeof(deg));
	memset(g,0,sizeof(g));
	memset(vis,0,sizeof(vis));
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t,kase=0;
	cin>>t;
	while(t--){
		kase++;
		n=50;
		cin>>m;
		init();
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			deg[u]++; deg[v]++;
			g[u][v]++; g[v][u]++;
		}
		int flag=1;
		for(int i=1;i<=n;i++){
			if(deg[i]&&deg[i]%2==1){
			//if(deg[i]&1){
				flag=0;
				break;
			}
		}
		int f;
		for(int i=1;i<=n;i++){
			if(deg[i]) {
				f=i;
				break;
			}
		}
		if(flag){
			dfs_2(f,0);
			for(int i=1;i<=n;i++){
				if(deg[i]&&vis[i]==0){
					flag=0;
					break;
				}
			}
		}
		cout<<"Case #"<<kase<<endl;
		if(flag){
			dfs(f);
		}else {
			cout<<"some beads may be lost"<<endl;
		}
		if(t!=0) cout<<endl;
	}
	return 0;
}
```
#### 求次小生成树的板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
typedef long long ll;
const int  N=1e5+50;
const int  M=1e6;
const ll INF=2e18;
ll n,m,ecnt=-1,tot;
ll fa[N],head[N];
ll dep[N],anc[N][25];
ll ancmax[N][25],ancmin[N][25];
ll totans=INF,sum=0;
bool vis[M];
struct _edge
{
    ll u,v,w;
}edge[M];

struct mint_edge
{
    ll nxt,u,v,w;
}e[M];
bool cmp(_edge a,_edge b)
{
    return a.w<b.w;
}
void addline(ll u,ll v,ll w)
{
    e[++ecnt].nxt=head[u];
    e[ecnt].v=v;
    e[ecnt].u=u;
    e[ecnt].w=w;
    head[u]=ecnt;
}
ll Find(ll x)
{
    if(x==fa[x]) return x;
    return fa[x]=Find(fa[x]);
}
void dfs(ll x,ll fa)
{
    dep[x]=dep[fa]+1;
    anc[x][0]=fa;
    for(ll i=head[x];~i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
    	ancmax[v][0]=e[i].w;
    	ancmin[v][0]=-INF;
		dfs(v,x);
    }
}
void cal()
{
	for(ll i=1;i<=18;++i)
	{
		for(ll x=1;x<=n;++x)
		{
			anc[x][i]=anc[anc[x][i-1]][i-1];
			ancmax[x][i]=max(ancmax[x][i-1],ancmax[anc[x][i-1]][i-1]);
			ancmin[x][i]=max(ancmin[x][i-1],ancmin[anc[x][i-1]][i-1]);
			if(ancmax[x][i-1]>ancmax[anc[x][i-1]][i-1]) ancmin[x][i]=max(ancmin[x][i],ancmax[anc[x][i-1]][i-1]);
			else if(ancmax[x][i-1]<ancmax[anc[x][i-1]][i-1]) ancmin[x][i]=max(ancmin[x][i],ancmax[x][i-1]);	
		}
	}
}
ll LCA(ll x,ll y)
{   
    if(dep[x]<dep[y]) swap(x,y);
    for(ll i=18;i>=0;--i)
    {
        if(dep[anc[x][i]]>=dep[y]) x=anc[x][i];        
    } 
    if(x==y) return x;
    for(ll i=18;i>=0;--i)
    {
    	if(anc[x][i]!=anc[y][i])
    	{
    		x=anc[x][i];
			y=anc[y][i];		
    	}
    }
    return anc[x][0];
}
ll getmax(ll x,ll fath,ll maxx)
{
	ll ans=-INF;
	for(ll i=18;i>=0;--i)
	{
		if(dep[anc[x][i]]>=dep[fath])
	    {
		// 	if(ancmax[x][i]!=maxx) ans=max(ans,ancmax[x][i]);     //严格次小生成树
		// 	else ans=max(ans,ancmin[x][i]);                       
            ans=max(ans,ancmax[x][i]);                            //求非严格次小生成树
			x=anc[x][i];
		}
	}
	return ans;
}
void init( void )
{
    memset(head,-1,sizeof(head));
    memset(anc,0,sizeof(anc));
    memset(ancmax,0,sizeof(ancmax));
    memset(ancmin,0,sizeof(ancmin));
    memset(vis,0,sizeof(vis));
    for(ll i=1;i<=n;++i) {
        fa[i]=i;
    }
    tot=0; ecnt=-1; totans=INF; sum=0;
}
void solve( void )
{
    cin>>n>>m;
    init();
    for(ll i=1;i<=m;++i)
    {
        ll x,y,z;
        cin>>x>>y>>z;
        edge[i].u=x;
        edge[i].v=y;
        edge[i].w=z;
    }
    sort(edge+1,edge+m+1,cmp);
    for(ll i=1;i<=m;++i)
    {
        ll x=Find(edge[i].u),y=Find(edge[i].v);
        if(x!=y)
        {
			fa[x]=y;
        	addline(edge[i].u,edge[i].v,edge[i].w);
        	addline(edge[i].v,edge[i].u,edge[i].w);
        	sum+=edge[i].w;
        	tot++;
        	vis[i]=true;
        	if(tot==n-1) break;
    	}
	}
	ancmin[1][0]=-INF;
    dfs(1,0);
    cal();
    totans=INF;
    for(ll i=1;i<=m;++i)
    {
    	if(!vis[i])
    	{
			ll x=edge[i].u,y=edge[i].v;
			ll fath=LCA(x,y);
			ll maxx=max(getmax(x,fath,edge[i].w),getmax(y,fath,edge[i].w));
            ll now=sum-maxx+edge[i].w;
            totans=min(totans,sum-maxx+edge[i].w);
    	}
	}
    if(totans==INF) cout<<sum<<" "<<sum<<endl;
    else cout<<sum<<" "<<totans<<endl;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```
#### 树形DP求树的直径_可用于负权图
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
#define mem(a,x) memset(a,x,sizeof(a));

const int N=1005;
const int M=10010;
int head[N],ver[N],edge[N],Next[N];
int v[N],dist[N];
int n,m,tot,ans;

void add(int x,int y,int w)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	edge[tot]=w;
}

void dp(int x)
{
	v[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(v[y]) continue;
		dp(y);
		ans=max(ans,dist[x]+dist[y]+edge[i]);
		dist[x]=max(dist[x],dist[y]+edge[i]);
	}
}

void init()
{
	mem(head,0);
	mem(v,0);
	mem(dist,0);
	tot=1;
	ans=INT_MIN;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int kase;
	cin>>kase;
	while(kase--){
		cin>>n>>m;
		init();
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			add(u,v,w);
			add(v,u,w);
		}
		dp(1);
		cout<<ans<<endl;
	}
	return 0;
}

```
#### 拓扑排序
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

int n;
map<char,int> m;
int g[30][30];
int dout[30];
int ok;
char ans[30];
char a[30];

void toposort(int cur)
{
	if(cur==n){
		for(int i=0;i<n-1;i++){
			cout<<ans[i]<<" ";
		}
		cout<<ans[n-1];
		cout<<endl;
		ok=1;
		return ;
	}else {
		for(int i=0;i<n;i++){
			if(dout[i]==0){
				dout[i]--;
				for(int j=0;j<n;j++){
					if(g[i][j]) dout[j]--;
				}
				ans[cur]=a[i];
				toposort(cur+1);
				dout[i]++;
				for(int j=0;j<n;j++){
					if(g[i][j]) dout[j]++;
				}
			}
		}
	}
}



int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t;
	string str;
	cin>>t;
	cin.get();
	while(t--){
		ok=0;
		n=0;
		m.clear();
		memset(g,0,sizeof(g));
		memset(dout,0,sizeof(dout));
		string str;
		getline(cin,str);
		getline(cin,str);
		char ch;
		for(int i=0;i<str.size();i++){
			if(isalpha(str[i])){
				a[n++]=str[i];
			}
		}
		sort(a,a+n);
		for(int i=0;i<n;i++) m[a[i]]=i;
		getline(cin,str);
		for(int i=0;i<str.size();i++){
			if(str[i]=='<'){
				char ch1,ch2;
				ch1=str[i-1];
				ch2=str[i+1];
				g[m[ch1]][m[ch2]]=1;
				dout[m[ch2]]++;
			}
		}

		toposort(0);
		if(!ok) cout<<"NO"<<endl;
		if(t!=0) cout<<endl;
 	}	
	return 0;
}
```
#### 网络最大流Dinic算法板子
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define endl "\n"

const int inf=1<<29,N=50010,M=300010;
int head[N],ver[M],edge[M],Next[M],d[N],now[M];
int n,m,s,t,tot,maxflow;

void add(int x,int y,int w)
{
	ver[++tot]=y; Next[tot]=head[x]; head[x]=tot; edge[tot]=w;
	ver[++tot]=x; Next[tot]=head[y]; head[y]=tot; edge[tot]=0;
}

bool bfs()
{
	memset(d,0,sizeof(d));
	queue<int> q;
	q.push(s); d[s]=1;
	now[s]=head[s];
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i];
			if(edge[i]&&!d[y]){
				q.push(y);
				now[y]=head[y];
				d[y]=d[x]+1;
				if(y==t) return 1;
			}
		}
	}
	return 0;
}

int dinic(int x,int flow)
{
	if(x==t) return flow;
	int rest=flow,k;
	for(int i=now[x];i&&rest;i=Next[i]){
		now[x]=i;
		int y=ver[i];
		if(edge[i]&&d[y]==d[x]+1){
			k=dinic(y,min(rest,edge[i]));
			if(!k) d[y]=0;
			edge[i]-=k;
			edge[i^1]+=k;
			rest-=k;
		}
	}
	return flow-rest;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	cin>>s>>t;
	tot=1;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
	}
	int flow=0;
	while(bfs()){
		while(flow=dinic(s,inf)) maxflow+=flow;
	}	
	cout<<maxflow<<endl;
	return 0;
}
```
#### 种子填充
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back
int H,W,mk;
int c[2000][2100];
char D[6]={'W','A','K','J','S','D'};
void drawgragh( char ch,int i,int j)
{
	int a[4];
	int num;
	if(isdigit(ch)){
		num=ch-'0';
	}else {
		num=(ch-'a')+10;
	}
	for(int i=3;i>=0;i--){
		a[i]=num%2;
		num/=2;
	}
	for(int jj=(j-1)*4+1,cnt=0;cnt<=3;cnt++){
		c[i][jj+cnt]=a[cnt];
	}
}


void dfs1(int x,int y )   //扣背景的函数
{
	if(x<1||x>H||y<1||y>W) return ;			//超出边界
	if(c[x][y]) return ;  
	c[x][y]=-1;
	for(int dx=-1;dx<=1;dx++){
		for(int dy=-1;dy<=1;dy++){
			//if(dx!=0||dy!=0) dfs1(x+dx,y+dy);
			dfs1(x+dx,y+dy);
		}
	}

}

void dfs2(int x,int y)
{
	if(x<1||x>H||y<1||y>W) return ;			
	if(c[x][y]==-1)  return;
	if(c[x][y]==1){
		c[x][y]=-1;
		for(int dx=-1;dx<=1;dx++){
			for(int dy=-1;dy<=1;dy++){
				//if(dx!=0||dy!=0) dfs2(x+dx,y+dy);
				dfs2(x+dx,y+dy);
			}
		}
	}else {
		mk++;
		dfs1(x,y);
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t=0;
	int h,w;
	while(cin>>h>>w&&h!=0){
		t++;
		H=h;
		W=w*4;
		priority_queue<char,vector<char>,greater<char> > pq;   //储存答案的优先队列
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++){
				char ch; cin>>ch;
				drawgragh(ch,i,j);
			}
		}
		//摸着边界扣背景
		for(int i=1;i<=H;i++){
			dfs1(i,1); dfs1(i,W);
		}
		for(int i=1;i<=W;i++){
			dfs1(1,i); dfs1(H,i);
		}

		for(int i=1;i<=H;i++){
			for(int j=1;j<=W;j++){
				if(c[i][j]==1){
					mk=0;
					dfs2(i,j);
					pq.push(D[mk]);
				}
			}
		}
		cout<<"Case "<<t<<": ";
		while(!pq.empty()) {
			char c=pq.top();
			pq.pop();
			cout<<c;
		}
		cout<<endl;
	}
	return 0;
}
```

#### tarjan算法与强连通分量
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define pb emplace_back

const int N=100000;
const int M=1000000;
int n,m;
int head[N],ver[M],Next[M];
int low[N],dfn[N],stacks[N],c[N],vis[N],tot,num,cnt,top;
vector<int> scc[N];

void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x)
{
	dfn[x]=low[x]=++num;
	stacks[++top]=x; vis[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnt++;
		int y;
		do{
			y=stacks[top--];
			vis[y]=0; c[y]=cnt;
			scc[cnt].pb(y);
		}while(x!=y);
	}
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	tot=1;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i);
	}
	return 0;
}
```