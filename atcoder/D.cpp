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
    int n, k;
    cin >> n >> k;
    vector<int> p(n + 1);
    for(int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        p[x] = i;
    }
    set<ll> idx;
    for(int i = 1; i <= k; ++i)
    {
        idx.insert(p[i]);
    }
    ll ans = *prev(idx.end()) - *idx.begin();
    for(int i = k + 1; i < n + 1; ++i)
    {
        int newIdx = p[i];
        int oldIdx = p[i - k];
        idx.erase(oldIdx);
        idx.insert(newIdx);
        ans = min(ans, *prev(idx.end()) - *idx.begin());
    }
    cout << ans << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}