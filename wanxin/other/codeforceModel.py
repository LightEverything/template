#######################################################
# change data : 2023 - 1 - 10
# user : wanxin
#######################################################
 
# import 
from operator import *
from functools import *
 
#######################################################
# return int
def initPrime(arr_isprime, arr_prime, int_many) :
    cnt = 1
    
    for i in range(2, int_many + 1) :
        if arr_isprime[i] :
            arr_prime.append(i)
            cnt += 1
 
        for j in range(1, cnt + 1) :
            if arr_prime[j] * i > int_many:
                break
            arr_isprime[arr_prime[j] * i] = 1
            if i % arr_prime[j] == 0:
                break
 
# return void
def fillArray(arr_array, T_elment, int_many) :
    for i in range(0, int_many + 1) :
        arr_array[i] = T_elment

# 并查集
def find(fa, x) :
    if x == fa[x] :
        return x
    else :
        return find(fa, fa[x])
 
def merge(a, b, fa, siz) :
    faa = find(fa, a)
    fbb = find(fa, b)
    if faa == fbb :
        return False
    fa[fbb] = faa
    siz[faa] += siz[fbb]
    return True
 
def init(n, fa, st, c, siz) :
 
    for i in range(0, n):
        fa[i] = i
        st[i] = 0
        c[i] = 0
        siz[i] = 1
 
#########################################################
 
# 参数定义 记得初始化
maxn = int(2E5 + 7)
# arr = [0] * maxn
##########################################################
 
# code start
def solve() :
    return
###########################################################
 
if __name__ == '__main__':
    T = 1
    T = int(input())
 
    while T :
        solve();
        T -= 1