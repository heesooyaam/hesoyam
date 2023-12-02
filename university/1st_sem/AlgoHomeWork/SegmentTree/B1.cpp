#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<unsigned long long> dp(1'005'000, 0);
    dp[1] = 1;
    long long l = 2, r = 3;
    long long d = 2;
    long long prevLen = 1;
    long long curLen = 2;
    for(long long i = 2; i < dp.size(); ++i)
    {
        if(i == l)
        {
            dp[i] = dp[i - prevLen] + i * i;
            l += d;
        }
        else if(i == r)
        {
            dp[i] = dp[i - prevLen - 1] + i * i;
            r += d + 1;
            d += 1;
            prevLen = curLen++;
        }
        else dp[i] = dp[i - prevLen] + dp[i - 1 - prevLen] + i * i - dp[i - 2 * prevLen];
    }
    long long t = 1; cin >> t;
    while(t--)
    {
        int x;
        cin >> x;
        cout << dp[x] << endl;
    }
    return 0;
}