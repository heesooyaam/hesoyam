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
const ll MOD = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    input(a);
    vector<map<ll, ll>> dp(n + 1);
    dp[0][0] = 1;
    for(int i = 0; i < n; ++i)
    {
        for(auto it : (dp[i].size() == 1) ? {dp[i].begin(), --dp[i].end()} : {})
        {
            auto&& [score, cnt] = *it;

            dp[i + 1][score + a[i]] += cnt;
            dp[i + 1][score + a[i]] %= MOD;
            dp[i + 1][llabs(score + a[i])] += cnt;
            dp[i + 1][llabs(score + a[i])] %= MOD;
        }
    }
    cout << prev(dp[n].end())->ss << endl;
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