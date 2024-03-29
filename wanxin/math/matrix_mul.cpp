#include <iostream>
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <cstring>

using namespace std;
const int mod = 1000000007;
const int maxn = 105;
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
                    (ans.val[i][j] += b.val[k][j] * r) %= mod;
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
                ans.val[i][j] = (val[i][j] + mt.val[i][j]) % mod;
            }
        return ans;
    }

    Matrix operator+(const Matrix &mt)
    {
        Matrix ans;

        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                ans.val[i][j] = (val[i][j] + mt.val[i][j]) % mod;
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

Matrix<long long> f;

signed main()
{
    int n, m;
    cin >> n >> m;

    f.val[0][0] = 2;
    for (int i = 1; i <= m - 1; i ++)
        f.val[i][0] = 1;
    Matrix<long long> a;
    a.val[0][0] = 1, a.val[0][m - 1] = 1;
    for (int i = 1; i < m; i ++)
        a.val[i][i - 1] = 1;
    if (n < m)
    {
        cout << 1;
        return 0;
    }
    f = matrixPow(a, n - m) * f;

    cout << f.val[0][0];
}