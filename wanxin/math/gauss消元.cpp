#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

template<typename T>
class Matrix
{
public:
    static const int maxn = 105;
    static const int mod = 1E9 + 7;
    static const int eps = 1E-7;
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


    // 高斯消元仅用于double矩阵
    bool gauss(double ans[], int n)
    {
        for (int i = 0; i < n; i ++)
        {
            int r = i;
            for (int j = i + 1; j < n; j ++)
                if (fabs(val[r][i]) < fabs(val[j][i]))
                    r = j;

            if (r != i) swap(val[r], val[i]);

            if (fabs(val[r][i]) <= eps)
                return false;

            double div = val[i][i];

            for (int j = i; j <= n; j ++)
                val[i][j] /= div;

            for (int j = i + 1; j < n; j ++)
            {
                div = val[j][i];
                for (int k = i; k <= n; k ++)
                    val[j][k] -= val[i][k] * div;
            }
        }
        
        ans[n - 1] = val[n - 1][n];
        for (int i = n - 2; i >= 0; i --)
        {
            ans[i] = val[i][n];
            for (int j = i + 1; j < n; j ++)
                ans[i] -= ans[j] * val[i][j];
        }
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

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    Matrix<double> a;
    for (int i = 0; i < n; i ++)
    for (int j = 0; j <= n; j ++)
    {
        cin >> a.val[i][j];
    }
    
    double ans[105];
    if (!a.gauss(ans, n))
    {
        cout << "No Solution" << '\n';
    }
    else 
    {
        for (int i = 0; i < n; i ++)
            cout << fixed << setprecision(2) << ans[i] << '\n';
    }
    
}