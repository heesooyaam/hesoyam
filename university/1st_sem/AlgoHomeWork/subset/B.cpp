#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
//#define endl '\n'   

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    input(a);
    vector<vector<ll>> rule(n, vector<ll> (n));
    for(int i = 0; i < k; ++i)
    {
        ll x, y;
        cin >> x >> y;
        cin >> rule[--x][--y];
    }
    vector<vector<ll>> dp(1 << (n), vector<ll> (n));
    ll ans = 0;
    for(int mask = 1; mask < dp.size(); ++mask)
    {
        if(__popcount(mask) > m) continue;

        for(int i = 0; i < n; ++i)
        {
            if((mask >> i) & 1)
            {
                if(__popcount(mask) == 1)
                {
                    dp[mask][i] = a[i];
                }
                else{
                    int submask = mask - (1 << i);
                    for(int j = 0; j < n; ++j)
                    {
                        assert(mask < dp.size() && submask < dp.size() && i < n && j < n);
                        if((submask >> j) & 1)
                        {
                            dp[mask][i] = max(dp[mask][i], dp[submask][j] + rule[j][i] + a[i]);
                            // cout << bitset<5>(submask) << ' ' << " cur: " << i << ' ' << " prev: " << j << " prevCnt: " << dp[submask][j] << "curCnt: " << dp[mask][i] << endl;
                        }
                    }
                }
                if(__popcount(mask) == m) ans = max(ans, dp[mask][i]);
            }
        }
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}