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
struct edge
{
    int to;
    ll len;
};
void dfs(vector<vector<edge>>& g, vector<ll>& dist, int cur, int prev)
{ 
    for(auto& [to, len] : g[cur])
    {
        if(to == prev) continue;

        dist[to] = dist[cur] + len;

        dfs(g, dist, to, cur);
    }
}  
void solve()
{
    int n;
    cin >> n;
    vector<vector<edge>> g(n + 1);
    ll ans = 0;
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to, len;
        cin >> from >> to >> len;
        ans += len * 2;
        g[from].pb({to, len});
        g[to].pb({from, len});
    }

    vector<ll> dist (n + 1, 0);

    dfs(g, dist, 1, -1);

    cout << ans - *max_element(all(dist)) << endl;

}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}