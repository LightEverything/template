#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;
int ans[105];

void gauss_xor(bitset<105> mt[])
{
    for (int i = 0; i < 30; i ++)
    {
        int r = i;
        for (int j = i + 1; j < 30; j ++)
            if (mt[j].test(i))
            {
                r = j;
                break;
            }
        if (r != i) swap(mt[r], mt[i]);
        for (int j = i + 1; j < 30; j ++)
        {
            if (mt[j].test(i))
                mt[j] ^= mt[i];
        }

    }

    ans[30 - 1] = mt[30 - 1].test(30);
    for (int i = 30 - 2; i >= 0; i --)
    {
        ans[i] = mt[i].test(30);
        for (int j = i + 1; j < 30; j ++)
            ans[i] ^= ans[j] * mt[i].test(j);
    }
}

int screen[10][10];
const int c = 6;
const int r = 5;
int cnt = 0;

void sovle()
{
    cnt = 0;
    bitset<105> mt[105];
    for (int i = 0; i < r; i ++)
        for (int j = 0; j < c; j ++)
            cin >> screen[i][j];

    for (int i = 0; i < r; i ++)
    for (int j = 0; j < c; j ++)
    {
        if (i - 1 >= 0)
            mt[cnt].set(cnt - 6);
        if (j - 1 >= 0)
            mt[cnt].set(cnt - 1);
        if (j + 1 <= 5)
            mt[cnt].set(cnt + 1);
        if (i + 1 <= 4)
            mt[cnt].set(cnt + 6);
        mt[cnt].set(30, screen[i][j]);
        mt[cnt].set(cnt);
        cnt ++;
    }
    gauss_xor(mt);

    for (int i = 0; i < 5; i ++)
    {
        for (int j = 0; j < 6; j ++)
        {
            cout << ans[i * 6 + j];
            if (j != 5)
                cout << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    
    int cnt = 0;

    while (T --)
    {
        cout << "PUZZLE #" << ++cnt << '\n';
        sovle();
    }
    return 0;
}