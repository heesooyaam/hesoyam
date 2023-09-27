#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
//#define endl '\n'   

const int MOD = 1e9 + 7;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<ll>> dp(k + 1, vector <ll> (n + 1));
    for(int i = 1; i <= n; ++i) dp[1][i] = 1;
    for(int len = 1; len <= k; ++len)
    {
        for(int num = 1; num <= n; ++num)
        {
            //cout << "dp[" << len << "][" << num << "] = " << dp[len][num] << endl; 
            for(int q = 1; len != k && q * num <= n; ++q)
            {
                dp[len + 1][num * q] += dp[len][num];
                dp[len + 1][num * q] %= MOD;
            }
        }
    }
    ull ans = 0;
    for(int i = 1; i <= n; ++i){ans += dp[k][i]; ans %= MOD;}
    cout << ans << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}