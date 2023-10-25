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
const int INF = 1e5;
void solve()
{
    int n; cin >> n;
    vector <int> count(INF + 1);
    for(int i = 0; i < n; i++)
    {
        int x; cin >> x;
        count[x]++;
    }
    vector <ll> dp(INF + 1);
    dp[0] = 0;
    dp[1] = count[1];
    for(int i = 2; i <= INF; i++)
    {
        dp[i] = max(dp[i - 1], dp[i - 2] + 1ll * count[i] * i);
    }
    cout << dp[INF] << endl;

}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}