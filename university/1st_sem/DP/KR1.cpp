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
    int n, mod;
    cin >> n >> mod;
    vector <int> c (n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }

    vector<vector<ll>> dp (n + 1, vector<ll> (3, 0));
    // dp[i][j] = amount of cases to paint i-th ball in j(1, 2 or 3) collor
    for(int i = 1; i <= n; ++i)
    {
        for(int cur : {0, 1, 2})
        {
            if(i == 1){
                if(c[i] == -1 || cur == c[i]) dp[i][cur] = 1;
                continue;
            }
            if(c[i] != -1 && cur != c[i]) continue;
            dp[i][cur] += dp[i - 1][(cur + 1) % 3] + dp[i - 1][(cur + 2) % 3];
            // cout << i << ' ' << cur << ": "  << dp[i][cur] << endl;
            dp[i][cur] %= mod;
        }
    }
    cout << (dp[n][0] + dp[n][1] + dp[n][2]) % mod << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}