/**
 * @file splay.cpp
 * @author lightevething (wanxinnb@outlook.com)
 * @brief 简短代码splay
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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