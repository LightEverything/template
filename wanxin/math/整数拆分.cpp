#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int mod = 998244353;
long long qpow(long long a, long long b, long long mod = mod)
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

    //均可
    Poly pow(long long k, int modx, long long k2 = 0)
    {
        k2 = (k2 == 0 ? k : k2);
        long long t = 0;
        for (t = 0; t < size() && a[t] == 0; t ++);
        long long inv = qpow(a[t], mod - 2);
        long long num = a[t];

        for (int i = 0; i < size() - t; i ++)
            a[i] = a[i + t] * inv % mod;
        for (int i = size() - t; i < size(); i ++)
            a[i] = 0;

        auto ans = log(size());

        Poly tmp;
        if (t * k > modx)
            tmp = Poly{0};
        else 
            tmp = Poly(t * k + 1), tmp[t * k] = qpow(num, k2);
        return ((ans * k).exp(size()) * tmp).modxk(modx);
    }

    int get_phi(int a)
    {
        int ans = 1;

        for (int i = 2; i * i <= a; i++)
        {
            if (a % i == 0)
            {
                ans *= (i - 1);
                a /= i;
                while (a % i == 0)
                {
                    a /= i;
                    ans *= i;
                }
            }
        }

        if (a != 1)
            ans *= (a - 1);

        return ans;
    }

    int getroot(int n)
    {
        int cnt = 0;
        map<int, int> mp;

        int num = get_phi(n);
        int tmp = num;

        int minrt = 0;
        for (int i = 2; i * i <= tmp; i++)
        {
            while (tmp % i == 0)
            {
                mp[i]++;
                tmp /= i;
            }
        }

        if (tmp != 1)
            mp[tmp]++;

        for (int g = 1; g <= n; g++)
        {
            if (__gcd(g, n) != 1)
                continue;

            bool flag = true;
            for (auto i : mp)
            {
                if (qpow(g, num / i.first, n) == 1)
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                minrt = g;
                break;
            }
        } 
        return minrt;
    }
};

const int maxn = 3E5 + 7;
long long fac[maxn];
long long invfac[maxn];

inline void initFacAndC(int n)
{
    fac[0] = 1;
    for (int i = 1; i <= n; i ++)
        fac[i] = fac[i - 1] *i % mod;
    invfac[n] = qpow(fac[n], mod - 2);
    invfac[0] = 1;

    for (int i = n - 1; i >= 1; i --)
        invfac[i] = (i + 1) * invfac[i + 1] % mod;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    Poly<long long> f(n + 1);

    for (int i = 1; i <= n; i ++)
    {
        Poly<long long> tmp(n + 1);
        long long inv = qpow(i, mod - 2);

        for (int j = i; j <= n; j += i)
            tmp[j] = inv;
        f = f + tmp;
    }
    f = f.exp(n + 1);

    for (int i = 1; i <= n; i ++)
        cout << f[i] << '\n';
    return 0;
}