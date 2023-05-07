from math import *

def exgcd(a, b):
    if not b:
        return 1, 0, a

    y, x, g = exgcd(b, a % b)
    y = y - a // b * x
    return x, y, g

def excrt(n, r, p):
    now_p = p[0]
    now_r = r[0]

    for i in range(1, n):
        x, y, g = exgcd(now_p, p[i])
        if (r[i] - now_r) % g != 0:
            return -1
        now_r = x * (r[i] - now_r) // g * now_p + now_r
        now_p = lcm(now_p, p[i])
        now_r = now_r % now_p
    return now_r;


n = int(input())
r = []
p = []

for i in range(0, n):
    tmpp, tmpr = map(int, input().split(" "))
    r.append(tmpr)
    p.append(tmpp)

ans = excrt(n, r, p)
print(ans)