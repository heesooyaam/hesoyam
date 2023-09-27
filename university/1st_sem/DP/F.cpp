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
    int start, finish;
    cin >> start >> finish;
    int time, d;
    cin >> time >> d;
    vector<unordered_map<int, int>> dp(time + 1);
    dp[1][start] = start;
    // for(int acceleration = -1 * d; acceleration <= d; ++acceleration)
    // {
    //     s.insert(start + acceleration);
    // }
    // s.insert(INT_MAX);
    for(int t = 1; t < time; ++t)
    {
        for(auto& [speed, dist] : dp[t])
        {
            int cur = speed;
            for(int acceleration = -1 * d; acceleration <= d; ++acceleration)
            {
                if(cur + acceleration - (time - t - 1) * d > finish or cur + acceleration + (time - t - 1) * d < finish) continue;
                if(auto search = dp[t + 1].find(cur + acceleration); search != dp[t + 1].end()) dp[t + 1][cur + acceleration] = max(dp[t + 1][cur + acceleration], dp[t][cur] + cur + acceleration);
                else dp[t + 1][cur + acceleration] = dp[t][cur] + cur + acceleration;
                //s.insert(cur + acceleration);
            }
            //s.pop();
        }
        //s.pop();
        //s.push(INT_MAX);
    }
    cout << dp[time][finish] << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}