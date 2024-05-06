//
// Created by topcr on 27.03.2024.
//
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
void dfs(vector<vector<int>>& g, vector<int>& color, vector<int>& dp, int start)
{

}
void sort(vector<vector<int>>& g, vector<int>& order, vector<bool>& used, int cur)
{
    used[cur] = true;
    for(auto& to : g[cur])
    {
        if(used[to]) continue;

        sort(g, order, used, to);
    }
    order.pb(cur);
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> color(n);
    input(color);
    vector<vector<int>> g(n);
    vector<bool> hasParent(n);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
    }
    vector<int> order;
    vector<bool> used(n);
    for(int v = 0; v < n; ++v)
    {
        if(used[v]) continue;
        sort(g, order, used, v);
    }
    vector<int> dp(n);
    used.assign(n, false);
    for(auto& v : order)
    {
        if(g[v].empty()) dp[v] = color[v];
        else
        {
            for(auto& child : g[v])
            {
                dp[v] = max(dp[v], dp[child] + (color[child] == 0 && color[v] == 1));
            }
        }
    }
    cout << *max_element(all(dp)) << endl;

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