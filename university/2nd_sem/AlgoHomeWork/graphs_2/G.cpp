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
    int n, m;
    cin >> n >> m;
    vector<ll> dist(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        cin >> dist[i];
    }
    unordered_map<int, ll> b;
    unordered_map<int, ll> e;
    ll ans = 0;
    for(int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        ans += labs(dist[x] - dist[y]);
        ++b[x];
        ++e[y];
    }
    bool ok = true;
    for(auto& [v, cnt] : e)
    {
        ok = b[v] == cnt;
        if(!ok) break;
    }
    if(ok) cout << ans << endl;
    else cout << -1 << endl;
}
int32_t main()
{
    freopen("bugged.in", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}