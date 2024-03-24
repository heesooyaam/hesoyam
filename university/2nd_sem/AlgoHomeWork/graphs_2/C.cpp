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

ll dfs(vector<unordered_set<int>>& g, vector<ll>& depth, vector<ll>& foo, int cur, int prev = 0)
{
    depth[cur] = depth[prev] + 1;
    for(auto& to : g[cur])
    {
        if(to == prev) continue;

        if(!depth[to])
        {
            foo[cur] = min({foo[cur], depth[cur], dfs(g, depth, foo, to, cur)});
        }
        else
        {
            foo[cur] = min(foo[cur], depth[to]);
        }
    }
    return foo[cur];
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    vector<unordered_set<int>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        edges[i] = {from, to};
        g[from].insert(to);
        g[to].insert(from);
    }
    vector<ll> depth(n + 1, 0);
    vector<ll> foo(n + 1, INT_MAX);
    dfs(g, depth, foo, 1);
    vector<int> ans;
    auto bridge = [&foo, &depth](int from, int to)->bool
    {
        return depth[from] < foo[to];
    };
    for(int i = 0; i < m; ++i)
    {
        if(depth[edges[i].ff] == depth[edges[i].ss]) continue;

        if(depth[edges[i].ff] > depth[edges[i].ss])
        {
            swap(edges[i].ff, edges[i].ss);
        }

        if(bridge(edges[i].ff, edges[i].ss)) ans.pb(i + 1);
    }
    cout << ans.size() << endl;
    print(ans);

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