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
    int n;
    cin >> n;
    vector <int> act(n + 1);
    for(int i = 1; i < n + 1; ++i){
        int x; cin >> x;
        act[i] = x + 1;
    }
    vector<vector<int>> dp(n + 1, vector <int> (4, INT_MAX)); // dp[day][action] = минимальное коичство дней отдыха если прошло day дней и в последний день занимался действием action
    // I were ... (1 - having rest, 2 - doing sport, 3 - solving problems)
    dp[0][1] = dp[0][2] = dp[0][3] = 0;
    for(int day = 1; day <= n; ++day)
    {
        int cur = act[day];
        for(int action = 1; action <= 3; ++action)
        {
            if(dp[day - 1][action] == INT_MAX) continue;
            dp[day][1] = min(dp[day][1], dp[day - 1][action] + 1);
            if((cur == 2 or cur == 4) and action != 2) dp[day][2] = min(dp[day][2], dp[day - 1][action]);
            if((cur == 3 or cur == 4) and action != 3) dp[day][3] = min(dp[day][3], dp[day - 1][action]);
        }
    }
    cout << *min_element(all(dp[n])) << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}