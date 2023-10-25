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
    vector <int> dp(n + 1);
    int a, b, c;
    cin >> a >> b >> c;
    for(int i = 0; i < n; ++i)
    {
        if(dp[i] == 0 and i != 0) continue;
        if(i + a <= n) dp[i + a] = max(dp[i + a], dp[i] + 1);
        if(i + b <= n) dp[i + b] = max(dp[i + b], dp[i] + 1);
        if(i + c <= n) dp[i + c] = max(dp[i + c], dp[i] + 1);
    }
    cout << dp[n] << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}