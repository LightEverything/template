#include <iostream>
#include <cmath>
#include <cstdio>
#include <initializer_list>

using namespace std;
const int mod = 1000000009;
template<typename T>
class Matrix
{
public:
    T val[4][4];
    Matrix(initializer_list<initializer_list<T>> l)
    {
        int i = 0, j = 0;

        for (auto& it : l)
        {
            for (auto& v : it)
                val[i][j ++] = v;
            i ++;
            j = 0;
        }
    }

    Matrix operator*(Matrix& b)
    {
        Matrix ans = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };

        for (int i = 0; i < 4; i ++)
            for (int j = 0; j < 4; j ++)
                for (int k = 0; k < 4; k ++)
                {
                    ans.val[i][j] = (ans.val[i][j] + (val[i][k] * b.val[k][j]) % mod) % mod;
                }

        return ans;
    }
};


template<typename T>
Matrix<T> matrixPow(Matrix<T>& a, int b)
{
    Matrix<T> ans = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    }; // e

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


int main(int argc, char** argv)
{
    Matrix<long long> a = {
        {2, 1, 0, 0},
        {0, 1, 1, 2},
        {0, 0, 1, 0},
        {0, 0, 1, 1}
    };

    long long num;
    while (cin >> num)
    {
        Matrix<long long> tmp = a;
        tmp = matrixPow(a, num % mod);
        long long ans = tmp.val[0][0] * 0 + tmp.val[0][1] * 1 + tmp.val[0][2] * 1 + tmp.val[0][3] * 1;
        cout << ans % mod << '\n';
    }

    return 0;
}