#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;
#define int long long 

template<typename T>
class Matrix
{
public:
    static const int maxn = 2;
    T val[maxn][maxn];

    Matrix(initializer_list<initializer_list<T>> l)
    {
        memset(val, 0, sizeof val);
        int i = 0, j = 0;

        for (auto &it : l)
        {
            for (auto &v : it)
                val[i][j++] = v;
            i++;
            j = 0;
        }
    }

    Matrix() { memset(val, 0, sizeof val); }

    Matrix operator*(const Matrix &b)
    {
        Matrix ans;
        T r = 0;

        for (int i = 0; i < maxn; i ++)
            for (int k = 0; k < maxn; k ++)
            {
                r = val[i][k];
                for (int j = 0; j < maxn; j ++)
                    ans.val[i][j] += b.val[k][j] * r;
            }

        return ans;
    }

    Matrix operator-()
    {
        Matrix ans;

        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                ans.val[i][j] -= val[i][j];
        return ans;
    }

    Matrix operator-(const Matrix &mt)
    {
        Matrix ans;

        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
            {
                ans.val[i][j] = val[i][j] + mt.val[i][j];
            }
        return ans;
    }

    Matrix operator+(const Matrix &mt)
    {
        Matrix ans;

        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                ans.val[i][j] = val[i][j] + mt.val[i][j];
        return ans;
    }

    bool isZero(const Matrix &mt)
    {
        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                if (mt.val[i][j])
                    return false;
        return true;
    }
};

template<typename T>
Matrix<T> geteMatrix()
{
    Matrix<T> e;
    for (int i = 0; i < e.maxn; i++)
        e.val[i][i] = 1;
    return e;
}

template<typename T>
Matrix<T> matrixPow(Matrix<T> &a, int b)
{
    Matrix<T> ans = geteMatrix<T>();
    Matrix<T> tmp = a;

    while (b)
    {
        if (b & 1)
            ans = ans * tmp;
        tmp = tmp * tmp;
        b >>= 1;
    }
    return ans;
}

const int maxn = 2E5 + 7;
int a[maxn];

class SegementTree
{
public:
    Matrix<double> val[maxn << 2];
    double lazy[maxn << 2];

    void build(int now, int l, int r)
    {
        if (l == r)
        {
            val[now] = {
                {sin(a[l] * 1.0), 0},
                {cos(a[l] * 1.0), 0}
            };
            return ;
        }

        int mid = l + r >> 1;
        build(now * 2, l, mid);
        build(now * 2 + 1, mid + 1, r);
        val[now] = val[now * 2] + val[now * 2 + 1];
    }

    void update(int now, int l, int r)
    {
        Matrix<double> tmp = {
            {cos(lazy[now]), sin(lazy[now])},
            {-sin(lazy[now]), cos(lazy[now])}
        };
        val[now * 2] =  tmp * val[now * 2], val[now * 2 + 1] = tmp * val[now * 2 + 1];
        lazy[now * 2] += lazy[now], lazy[now * 2 + 1] += lazy[now];
        lazy[now] = 0;
    }

    void change(int now, int l, int r, int nl, int nr, int x)
    {
        if (nl <= l && nr >= r)
        {
            Matrix<double> tmp = {
                {cos(x), sin(x)},
                {-sin(x), cos(x)}
            };
            val[now] = tmp * val[now];
            lazy[now] += x;
            return ;
        }

        if (lazy[now]) update(now, l, r);

        int mid = l + r >> 1;
        if (nl <= mid) change(now * 2, l, mid, nl, nr, x);
        if (nr >= mid + 1) change(now * 2 + 1, mid + 1, r, nl, nr, x);
        val[now] = val[now * 2] + val[now * 2 + 1];
    }

    Matrix<double> query(int now, int l, int r, int nl, int nr)
    {
        if (nl <= l && nr >= r)
        {
            return val[now];
        }

        if (lazy[now]) update(now, l, r);

        int mid = l + r >> 1;
        Matrix<double> ans;
        if (nl <= mid)  ans = ans + query(now * 2, l, mid, nl, nr);
        if (nr >= mid + 1)  ans = ans + query(now * 2 + 1, mid + 1, r, nl, nr);
        return ans;
    }
};

SegementTree st;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++)
        cin >> a[i];

    st.build(1, 1, n);
    int m;
    cin >> m;
    while (m --)
    {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1)
        {
            int v;
            cin >> v;
            st.change(1, 1, n, l, r, v);
        }
        else 
        {
            cout <<fixed << setprecision(1) << st.query(1, 1, n, l, r).val[0][0] +  0.05 << '\n';
        }
    }
    
}