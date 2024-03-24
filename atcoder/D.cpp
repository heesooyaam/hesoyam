#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ss second
#define ff first
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   
#define int int64_t

void solve()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> cost(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> cost[i];
    }
    int cnt = 0;
    for(int i = 0; i < n - 1 && cnt <= 1; ++i)
    {
        if(s[i] == s[i + 1]) ++cnt;
    }
    if(cnt == 1)
    {
        cout << 0 << endl;
        return;
    }
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>> (2, vector<ll> (2)));
    dp[1][0][0] = cost[1] * (s[0] != '0');
    dp[1][0][1] = cost[1] * (s[0] != '1');
    dp[1][1][0] = numeric_limits<ll>::max();
    dp[1][1][1] = numeric_limits<ll>::max();
    for(int i = 2; i <= n; ++i)
    {
        dp[i][0][0] = dp[i - 1][0][1] + cost[i] * int64_t(s[i - 1] != '0');
        dp[i][0][1] = dp[i - 1][0][0] + cost[i] * (s[i - 1] != '1');
        dp[i][1][0] = min(dp[i - 1][0][0], dp[i - 1][1][1]) + cost[i] * int64_t(s[i - 1] != '0');
        dp[i][1][1] = min(dp[i - 1][0][1], dp[i - 1][1][0]) + cost[i] * int64_t(s[i - 1] != '1');
    }
    cout << min(dp[n][1][0], dp[n][1][1]) << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}