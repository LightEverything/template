#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const int mod = 998244353;
long long qpow(long long a, long long b)
{
    long long ans = 1;
    long long tmp = a;
    while (b)
    {
        if (b & 1)
            ans = ans * tmp % mod;
        tmp = tmp * tmp % mod;
        b >>= 1;
    }

    return ans;
}

template<typename T>
class Poly
{
public:
    vector<T> a;
    Poly() {};
    
    explicit Poly(const int siz): a(siz){}
    Poly(const vector<T>& v): a(v){}
    Poly(const initializer_list<T>& v): a(v){}

    void resize(int n)
    {
        a.resize(n);
    }

    int size() const 
    {
        return a.size();
    }

    T& operator[](const int idx)
    {
        return a[idx];
    }

    T operator[](const int idx) const
    {
        if (idx < a.size())
            return a[idx];
        else 
            return 0;
    }

    void change(int len)
    {
        for (int i = 1, j = len / 2, k; i < len - 1; i++)
        {
            if (i < j)
                swap(a[i], a[j]);
            k = len / 2;
            while (j >= k)
            {
                j -= k;
                k /= 2;
            }
            if (j < k)
                j += k;
        }
    }

    void ntt(int len, int i)
    {
        change(len);

        for (int h = 2; h <= len; h <<= 1)
        {
            long long gn = qpow(3, (mod - 1) / h);
            if (i == -1)
                gn = qpow(gn, mod - 2);
            for (int j = 0; j < len; j += h)
            {
                long long g = 1;
                for (int k = j; k < j + h / 2; k++)
                {
                    long long u = a[k], v = g * a[k + h / 2] % mod;
                    a[k] = (u + v) % mod;
                    a[k + h / 2] = (u - v + mod) % mod;
                    g = g * gn % mod;
                }
            }
        }

        if (i == -1)
        {
            long long inv = qpow(len, mod - 2);
            for (int i = 0; i < len; i++)
                a[i] = a[i] * inv % mod;
        }
    }

    void dft(int len)
    {
        ntt(len, 1);
    }

    void idft(int len)
    {
        ntt(len, -1);
    }

    Poly modxk(int k)
    {
        k = min(k, int(a.size()));
        return Poly(vector<T>(a.begin(), a.begin() + k));
    }


    friend Poly operator*(Poly a, Poly b)
    {
        if (a.size() == 0 || b.size() == 0)
            return Poly();

        int len = 1, tot = a.size() + b.size() - 1;
        while (len < tot)   len <<= 1;
        a.resize(len);
        b.resize(len);
        
        a.dft(len);
        b.dft(len);
        
        for (int i = 0; i < len; i ++)
            a[i] = a[i] * b[i] % mod;
        a.idft(len);
        a.resize(tot);
        return a;
    }

    friend Poly operator*(Poly a, int b)
    {
        for (int i = 0; i < a.size(); i ++)
            a[i] = a[i] * b % mod;
        return a;
    }

    friend Poly operator*(int a, Poly b)
    {
        for (int i = 0; i < b.size(); i ++)
            b[i] = b[i] * a % mod;
        return b;
    }

    friend Poly operator-(const Poly& aa, const Poly& b)
    {
        vector<T> res(max(aa.size(), b.size()));
        for (int i = 0; i < int(res.size()); i ++)
        {
            res[i] = ((aa[i]- b[i]) % mod + mod) % mod;
        }
        return Poly(res);
    }

    friend Poly operator+(const Poly& aa, const Poly& b)
    {
        vector<T> res(max(aa.size(), b.size()));
        for (int i = 0; i < int(res.size()); i ++)
        {
            res[i] = (aa[i]+ b[i]) % mod;
        }
        return Poly(res);
    }

    // 第一项是1
    Poly inv(int m)
    {
        Poly res{qpow(a[0], mod - 2)};

        int k = 1;
        while (k < m)
        {
            k <<= 1;
            res = (res * (Poly{2LL} - modxk(k) * res)).modxk(k);
        }
        return res.modxk(m);
    }

    // 第一项是1
    Poly sqrt(int m)
    {
        Poly res{1};
        int k = 1;

        while (k < m)
        {
            k <<= 1;
            res = ((res + (modxk(k) * res.inv(k))).modxk(k)) * ((mod + 1) / 2);
        }
        return res.modxk(m);
    }

    Poly deriv()
    {
        if (a.empty())
            return Poly();
        Poly ans(size() - 1);
        for (int i = 0; i < size() - 1; i ++)
            ans[i] = a[i + 1] * (i + 1) % mod;
        return ans;
    }

    // 这里可以提前预处理
    Poly integr()
    {
        Poly ans(size() + 1);

        for (int i = 0; i < size(); i ++)
            ans[i + 1] = a[i] * qpow(i + 1, mod - 2) % mod;
        return ans;
    }

    // 第一项是1
    Poly log(int m)
    {
        return (deriv() * inv(m)).integr().modxk(m);
    }

    // 第一项为0
    Poly exp(int m)
    {
        Poly ans{1};
        int k = 1;
        while (k < m)
        {
            k <<= 1;
            ans = (ans * (Poly{1} - ans.log(k) + modxk(k))).modxk(k);
        }
        return ans.modxk(m);
    }

    Poly pow(long long k)
    {
        auto ans = log(size());
        for (int i = 0; i < size(); i ++)
            ans[i] = ans[i] * k % mod;
        return ans.exp(size());
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    string k;
    long long k1 = 0;
    cin >> n >> k;

    // reverse(k.begin(), k.end());
    for (int i = 0; i < k.size(); i ++)
    {
        k1 = k1 * 10 + k[i] - '0';
        k1 %= mod;
    }

    Poly<long long> f(n);
    for (int i = 0; i < n; i ++)
        cin >> f[i];

    f = f.pow(k1);
    for (int i = 0; i < n; i ++)
    {
        cout << f[i] << ' ';
    }

}