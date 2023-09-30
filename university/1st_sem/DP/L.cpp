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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> dp(n + 2, vector<ll> (k + 1));
    vector <ll> pref(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        cin >> pref[i];
        pref[i] += pref[i - 1];
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j <= min((i - 1) / m, k); ++j)
        {
            if(i + m <= n + 1 && j < k) dp[i + m][j + 1] = max(dp[i][j] + pref[i + m - 1] - pref[i - 1], dp[i + m][j + 1]);
            dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
        }
    }
    cout << dp[n + 1][k] << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}