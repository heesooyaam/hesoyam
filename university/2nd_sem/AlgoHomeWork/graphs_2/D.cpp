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
#define print(x); for(auto& val : x){cout << val << '\n';}
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   
set<int> ans;
void dfs(vector<vector<int>>& g, vector<int>& depth, vector<int>& up, int cur, int prev = 0)
{
    depth[cur] = depth[prev] + 1;
    up[cur] = depth[cur];
    int dfsChilds = 0;
    // cout << cur << endl;
    for(auto& to : g[cur])
    {
        if(depth[to])
        {
            up[cur] = min(depth[to], up[cur]);
        }
        else
        {
            ++dfsChilds;
            dfs(g, depth, up, to, cur);
            up[cur] = min(up[cur], up[to]);
            if(prev != 0 && depth[cur] <= up[to])
            {
                ans.insert(cur);
            }
        }
    }
    if(prev == 0)
    {
        if(dfsChilds >= 2) ans.insert(cur);
    }
    
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
        g[to].pb(from);
    }
    vector<int> depth(n + 1, 0);
    vector<int> up(n + 1, INT_MAX);
    for(int v = 1; v <= n; ++v)
    {
        if(depth[v]) continue;
        else dfs(g, depth, up, v);
        // cout << "!!!" << endl; cout.flush();
    }
    cout << ans.size() << endl;
    print(ans);
}
int32_t main()
{
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}