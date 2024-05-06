//
// Created by topcr on 03.04.2024.
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
#define int int64_t
void dfs(vector<vector<int>>& g, vector<ll>& color, vector<map<ll, ll>>& g_mp, vector<pair<ll, ll>>& ans, int cur, int prev = -1)
{
    ll mx = 1;
    ll cnt = color[cur];
    g_mp[cur][color[cur]] = 1;
    for(auto& to : g[cur])
    {
        if(to == prev) continue;

        dfs(g, color, g_mp, ans, to, cur);
        if(g_mp[cur].size() < g_mp[to].size())
        {
            swap(g_mp[cur], g_mp[to]);

            mx = ans[to].ff;
            cnt = ans[to].ss;
        }
        for(auto& [v, amt] : g_mp[to])
        {
            g_mp[cur][v] += amt;
            if(val > mx)
            ll val = g_mp[cur][v];
            {
                mx = val;
                cnt = v;
            }
            else if(val == mx)
            {
                cnt += v;
            }
        }
    }
    ans[cur] = {mx, cnt};

}
void solve()
{
    int n;
    cin >> n;
    vector<ll> color(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> color[i];
    }
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
        g[to].pb(from);
    }
    vector<map<ll, ll>> g_mp(n + 1);
    vector<pair<ll, ll>> ans(n + 1);
    dfs(g, color, g_mp, ans, 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cout << ans[i].ss << ' ';
    }
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