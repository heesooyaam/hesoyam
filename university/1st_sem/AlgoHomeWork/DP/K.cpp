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
const ll MAX = 1e5 + 1;
const ll MOD = 1e9 + 7;
void solve()
{
    int T;
    cin >> T;
    int k;
    cin >> k;
    vector<ll> dp(MAX);
    dp[0] = 1;
    for(int i = 0; i < MAX - 1; ++i)
    {
        dp[i + 1] += dp[i];
        dp[i + 1] %= MOD;
        if(i + k < MAX)
        {
            dp[i + k] += dp[i];
            dp[i + k] %= MOD;
        }
        
    }
    vector<ll> pref(MAX, 0);
    for(int i = 1; i < MAX; ++i)
    {
        pref[i] = pref[i - 1] + dp[i];
        pref[i] %= MOD;
    }
    while(T--)
    {
        int a, b;
        cin >> a >> b;
        cout << (pref[b] >= pref[a - 1] ? pref[b] - pref[a - 1] : MOD + pref[b] - pref[a - 1]) << endl;
    }
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}