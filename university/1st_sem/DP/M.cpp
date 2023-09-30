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
#define endl '\n'   

void solve()
{
    int n, m, b, mod;
    cin >> n >> m >> b >> mod;
    vector <int> mistakes (n);
    for(int i = 1; i < n + 1; i++)
    {
        cin >> mistakes[i];
    }
    vector<vector<int>> dp(m + 1, vector <int> (b + 1));
    dp[0][0] = 1;
    // dp[i][j][k] = amount of good plans to complete j strings with k mistakes using i programmists
    for(int i = 1; i <= n; ++i) // choosing proger
    {
        for(int j = 0; j < m; ++j) // choosing amount of written strings
        {
            for(int k = 0; k < b + 1; ++k) // choosing amount of mistakes 
            {
                dp[j + 1][k] += dp[j][k];
                dp[j + 1][k] %= mod;
                if(k + mistakes[i] <= b){
                    dp[j + 1][k + mistakes[i]] += dp[j][k];
                    dp[j + 1][k + mistakes[i]] %= mod; 
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i <= b; ++i)
    {
        ans += dp[m][i];
    }
    cout << ans % mod << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}