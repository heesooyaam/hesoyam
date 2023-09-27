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
const ll INF = 1e15;
void solve()
{
    int n;
    cin >> n;
    vector <int> c(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        cin >> c[i];
    }
    vector <vector<string>> str(n + 1, vector<string> (2));
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> str[i][0];
        string reversed = str[i][0];
        reverse(all(reversed));
        str[i][1] = reversed;
    }
    vector<vector<ll>> dp(n + 1, vector<ll> (2));
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(auto& j : {0, 1})
        {
            ll case1 = INF, case2 = INF;
            if(str[i][j] >= str[i - 1][0]) case1 = dp[i - 1][0];
            if(str[i][j] >= str[i - 1][1]) case2 = dp[i - 1][1];
            dp[i][j] = (j * c[i] + min(case1, case2)) >= INF ? INF : j * c[i] + min(case1, case2); 
        }
    }
    if(min(dp[n][0], dp[n][1]) == INF) cout << -1 << endl;
    else cout << min(dp[n][0], dp[n][1]) << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}