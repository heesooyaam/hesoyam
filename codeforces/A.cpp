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
    int n;
    cin >> n;
    vector<int> ogr;
    int l = INT_MIN;
    int r = INT_MAX;
    for(int i = 0; i < n; ++i)
    {
        int type;
        cin >> type;
        int x;
        cin >> x;
        if(type == 3)
        {
            if(x <= r && x >= l) ogr.pb(x);
        }
        else if(type == 1) l = max(l, x);
        else r = min(r, x);
    }
    make_unique(ogr);
    auto ptrL = lower_bound(all(ogr), l);
    auto ptrR = upper_bound(all(ogr), r);
    // cout << ptrR - ptrL << endl;
    cout << max(0, r - l + 1) - max((int64_t) (ptrR - ptrL), 0ll) << endl;

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