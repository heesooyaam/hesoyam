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
    int m;
    cin >> m;
    vector<ll> vec(m);
    input(vec);
    make_unique(vec);
    vector<ll> d(vec.size());
    int n = vec.size();
    for(int i = 1; i < n; ++i)
    {
        d[i] = vec[i] - vec[i - 1];
    }
    vector<ll> pref(n);
    for(int i = 1; i < n; ++i)
    {
        pref[i] = pref[i - 1] + d[i];
    }
    // print(pref);
    ll ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ans = max(ans, upper_bound(pref.begin() + i, pref.end(), m - 1 + pref[i]) - (pref.begin() + i));
    }
    cout << ans << endl;
    
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