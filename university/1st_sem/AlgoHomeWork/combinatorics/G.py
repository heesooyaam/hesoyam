MOD = 10**9 + 7
for i in range (int(input())):
    n, k = map(int, input().split())
    print(n ** k % MOD, sep = '\n')