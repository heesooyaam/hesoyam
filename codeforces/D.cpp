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
#define rall(x) (x).rbegin(),(x).rend()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   
void solve()
{
    int n;
    cin >> n;
    vector<ll> vec(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> vec[i];
    }
    vector<ll> dp(n + 1, 0);
    vector<ll> sum;
    ll add = 0;
    for(int i = 1; i < n + 1; ++i)
    {
        if(upper_bound(rall(sum), vec[i] - add) == sum.rend())
        {
            dp[i] = -1;
            sum.clear();
            sum.pb(vec[i]);
            add = 0;
        } 
        else
        {
            dp[i] = upper_bound(rall(sum), vec[i] - add) - sum.rbegin() + 1;
            sum.pb(sum.back() + vec[i]);
            add += vec[i];
        }
    }
    sum.clear();
    // print(dp);
    add = 0;
    for(int i = n; i >= 1; --i)
    {
        if(upper_bound(rall(sum), vec[i]) == sum.rend())
        {
            sum.clear();
            sum.pb(vec[i]);
            add = 0;
        } 
        else
        {
            dp[i] = min(((dp[i] == -1) ? numeric_limits<ll>::max() : dp[i]), upper_bound(rall(sum), vec[i]) - sum.rbegin() + 1);
            sum.pb(sum.back() + vec[i]);
            add += vec[i];
        }
    }
    for(int i = 1; i < n + 1; ++i)
    {
        cout << dp[i] << ' ';
    }
    cout << endl;
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