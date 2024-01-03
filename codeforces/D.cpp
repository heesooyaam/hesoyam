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

void solve()
{
    int n;
    cin >> n;
    vector<vector<ll>> act(3, vector<ll> (n + 1));
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 1; j < n + 1; ++j) cin >> act[i][j];
    }
    vector<vector<vector<vector<ll>>>> dp(n + 1, vector<vector<vector<ll>>> (2, vector<vector<ll>> (2, vector<ll> (2, 0))));
    for(int day = 0; day < n; ++day)
    {
        for(int i : {0, 1})
        {
            for(int j : {0, 1})
            {
                for(int k : {0, 1})
                {
                    if(i == 0)
                    {
                        dp[day + 1][1][j][k] = max(dp[day + 1][1][j][k], dp[day][i][j][k] + act[0][day + 1]);
                    }
                    if(j == 0)
                    {
                        dp[day + 1][i][1][k] = max(dp[day + 1][i][1][k], dp[day][i][j][k] + act[1][day + 1]);
                    }
                    if(k == 0)
                    {
                        dp[day + 1][i][j][1] = max(dp[day + 1][i][j][1], dp[day][i][j][k] + act[2][day + 1]);
                    }
                    dp[day + 1][i][j][k] = max(dp[day + 1][i][j][k], dp[day][i][j][k]);
                }
            }
        }
    }
    cout << dp[n][1][1][1] << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}