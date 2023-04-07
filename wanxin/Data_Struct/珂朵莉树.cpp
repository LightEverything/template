/**
 * @file 珂朵莉树.cpp
 * @author lightevething (wanxinnb@outlook.com)
 * @brief 珂朵莉树模板
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;
const int maxn = 1E5 + 7;
const int mod = 1000000007;

#define int long long 
long long  ksm(long long  x, long long  y, long long  p) {
    long long  r = 1;
    long long  base = x % p;
    while (y) {
        if (y & 1) {
            r = r * base % p;
        }
        base = base * base % p;
        y >>= 1;
    }
    return r;
}

long long n, m, seed, vmax;
int a[maxn];
struct node 
{
    long long l, r;
    mutable long long v;

    node(long long ll, long long rr = 0, long long vv = 0) : l(ll), r(rr), v(vv){}
    bool operator<(const node& a) const 
    {
        return l < a.l;
    }
};

struct rnode
{
    long long num, cnt;

    rnode(long long n, long long c) : num(n), cnt(c) {}
    bool operator<(const rnode& a) const
    {
        return num < a.num;
    }
};

set<node> s;

set<node>::iterator split(int pos)
{
    auto it = s.lower_bound(node(pos));
    if (it != s.end() && it->l == pos)
        return it;
    it --;
    if (it->r < pos)    return s.end();
    long long l = it->l;
    long long r = it->r;
    long long v = it->v;
    s.erase(it);
    s.insert(node(l, pos - 1, v));
    return s.insert(node(pos, r, v)).first;
}

void assign(long long l, long long r, long long x)
{
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, x));
}

void add(long long l, long long r, long long x)
{
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; it ++)
        it->v += x;
}

long long rnk(long long l, long long r, long long x)
{
    auto itr = split(r + 1), itl = split(l);
    vector<rnode> v;
    for (auto it = itl; it != itr; it ++)
    {
        v.push_back(rnode(it->v, it->r - it->l + 1));
    }
    sort(v.begin(), v.end());
    int i = 0;
    for (i = 0; i < v.size(); i++)
    {
        if (v[i].cnt < x)
            x -= v[i].cnt;
        else 
            break;
    }
    return v[i].num;
}

long long calP(long long l, long long r, long long x, long long y) {
    set<node>::iterator itr = split(r + 1), itl = split(l);
    long long ans = 0;
    for (set<node>::iterator i = itl; i != itr; ++i) {
        long long p = ksm(i->v, x, y);
        p = p *(i->r - i->l + 1) % y;
        ans += p;
        ans %= y;
    }
    return ans;
}

long long rnd() 
{
    long long ret = seed;
    seed = (seed * 7 + 13) % mod;
    return ret;
}

signed main() {
    cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
        s.insert(node(i, i, a[i]));
    }
    for (int i = 1; i <= m; ++i) {
        long long op, l, r, x, y;
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
        } else {
            x = (rnd() % vmax) + 1;
        }
        if (op == 4) {
            y = (rnd() % vmax) + 1;
        }
        if (op == 1) {
            add(l, r, x);
        } else if (op == 2) {
            assign(l, r, x);
        } else if (op == 3) {
            cout << rnk(l, r, x) << endl;
        } else {
            cout << calP(l, r, x, y) << endl;
        }
    }
    return 0;
}