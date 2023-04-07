/**
 * @file kmp.cpp
 * @author lightEvething (wanxinnb@outlook.com)
 * @brief 简单kmp版本
 * @date 2022-09-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <string>

using namespace std;
string str1, str2;
const int maxn = 1E6 + 7;
int nexta[maxn];

void  initkmp()
{
    int size2 = str2.size();
    int cnt = 0;
    nexta[0] = -1;

    for (int i = 2; i <= size2; i++)
    {
        while (cnt && str2[i - 1] != str2[cnt])
            cnt = nexta[cnt];
        if (str2[i - 1] == str2[cnt])
            cnt ++;
        nexta[i] = cnt;
    }
    return ;
}

int main(int argc ,char** argv)
{
    cin >> str1 >> str2;

    int j = 0, i = 0;
    initkmp();

    for (int i  = 0; i < str1.size(); i++)
    {
        while (j && str1[i] != str2[j])
            j = nexta[j];
        if (str1[i] == str2[j])
            j ++;
        if (j == str2.size())   
        {
            cout << i - j  + 2 << '\n';
            j = nexta[j];
        }
    }

    for (int i = 1; i <= str2.size(); i++)
        cout << nexta[i] << ' ';
    return 0;
}