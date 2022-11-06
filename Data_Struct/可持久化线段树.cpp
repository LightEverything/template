#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

template<typename T>
class PersistableSegmentTree
{
public:
    static constexpr int maxn = 4 * (1E6 + 1E6 * log2(1E6)) + 7;
    T lch[maxn], rch[maxn], e[maxn], root[maxn], tree[maxn];
    int cnt = 0;

    void build(T& now, int l, int r)
    {
        now = ++cnt;
        if (l == r)
        {
            tree[now] = a[l];
            return ;
        }

        int mid = (l + r) / 2;
        build(lch[now], l, mid);
        build(rch[now], mid + 1, r);
    }

    void copyPath(T now, T pre)
    {
        lch[now] = lch[pre];
        rch[now] = rch[pre];
        tree[now] = tree[pre];
    }

    void change(T & now, T pre, int l, int r, int pos, T v)
    {
        now = ++cnt;
        copyPath(now, pre);
        if (l == r)
        {
            tree[now] = v;
            return ;
        }
        
        int mid = (l + r) /2;
        if (pos <= mid) 
            change(lch[now], lch[pre], l, mid, pos ,v);
        if (pos >= mid + 1) 
            change(rch[now], rch[pre], mid + 1, r, pos, v);
    }

    T query(T now,  int l, int r, int pos)
    {
        if (l == r && l == pos) 
           return tree[now];
        int mid = (l + r) / 2;
        if (pos <= mid) return query(lch[now], l, mid, pos);
        if (pos >= mid + 1) return query(rch[now], mid + 1, r, pos);
    }
};