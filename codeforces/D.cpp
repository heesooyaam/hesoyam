#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
// #define eb emplace_back
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
    int n, m;
    cin >> n >> m;
    multiset<ll> a, b;
    for(int i = 0; i < n; ++i)
    {
        ll x;
        cin >> x;
        a.insert(x);
    }
    for(int i = 0; i < m; ++i)
    {
        ll x;
        cin >> x;
        b.insert(x);
    }
    
    // print(a);
    ll ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ll bb = abs(*a.begin() - *b.begin());
        ll be = abs(*a.begin() - *prev(b.end()));
        ll ee = abs(*prev(a.end()) - *prev(b.end()));
        ll eb = abs(*prev(a.end()) - *b.begin());
        ll mx = max({bb, be, ee, eb});
        ans += mx;
        if(mx == bb)
        {
            a.erase(a.begin());
            b.erase(b.begin());
        }
        else if(mx == be)
        {
            a.erase(a.begin());
            b.erase(prev(b.end()));
        }
        else if(mx == ee)
        {
            a.erase(prev(a.end()));
            b.erase(prev(b.end()));
        }
        else
        {
            a.erase(prev(a.end()));
            b.erase(b.begin());
        }
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