#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
#include <vector>

using namespace std;

void change(complex<double> a[], int len)
{

    for (int i = 1, j = len / 2, k; i < len - 1;  i ++)
    {
        if (i < j) swap(a[i], a[j]);
        k = len / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void fft(complex<double> a[], int len, int i)
{
    change(a, len);

    for (int h = 2; h <= len; h <<= 1)
    {
        complex<double> wn(cos(i * 2 * M_PI / h), sin(i * 2 * M_PI / h));
        for (int j = 0; j < len; j += h)
        {
            complex<double> w(1, 0);
            for (int k = j; k < j + h / 2; k ++)
            {
                complex<double> u = a[k], v = w * a[k + h / 2];
                a[k] = u + v;
                a[k + h / 2] = u - v;
                w = w * wn;
            }
        }
    }

    if (i == -1)
        for (int i = 0; i < len; i ++)
            a[i].real(a[i].real() / len);
}

const int maxn = 2E5 + 7;
int len = 1;
int lens, lent;
string s, t;
int k;
complex<double> fta[maxn * 4], fsa[maxn * 4], fsc[maxn * 4], ftc[maxn * 4], ftg[maxn * 4], fsg[maxn * 4], fst[maxn * 4], ftt[maxn * 4], ans[maxn * 4];

void solve(char c, complex<double> fs[], complex<double> ft[])
{
    vector<int> sum(lens + 1);

    for (int i = 0; i < lens; i ++)
        sum[i] = s[i] == c;
    for (int i = 1; i < lens; i ++)
        sum[i] += sum[i - 1];

    for (int i = 0; i < lent; i ++)
        if (t[i] == c)  ft[i].real(1);
    for (int i = 0, j = lens - 1; i < lens; i ++, j --)
    {
        int l = max(0, i - k) - 1;
        l = (l == -1) ? 0 : sum[l];
        int r = min(lens - 1, i + k);
        r = sum[r];

        if (r - l) fs[j].real(1);
    }

    fft(ft, len, 1);
    fft(fs, len, 1);

    for (int i = 0; i < len; i ++)
        ans[i] += fs[i] * ft[i];
        
}

int main()
{
    cin >>lens >> lent >> k >> s >> t;
    while (len < lens * 2) len <<= 1;
    
    solve('A', fsa, fta);
    solve('T', fst, ftt);
    solve('C', fsc, ftc);
    solve('G', fsg, ftg);

    fft(ans, len, -1);
    int res = 0;

    for (int i = 0; i < lens; i ++)
    {
        int num = ans[lens - i].real() + 0.5;
        if (num >= lent) res ++;
    }
    cout << res << '\n';
}