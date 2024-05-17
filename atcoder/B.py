n = int(input())
arr = list(reversed([int(i) for i in input().split()]))

d = dict()
ans = 0
mod = 998244353
for i in range(n):
    cnt = n - i - 1
    ans += cnt * arr[i]
    ans %= mod
    for length, v in d.items():
        ans += v * arr[i] * (10**length)
        ans %= mod
    if len(str(arr[i])) in d:
        d[len(str(arr[i]))] += 1
    else:
        d[len(str(arr[i]))] = 1

print(ans % mod)