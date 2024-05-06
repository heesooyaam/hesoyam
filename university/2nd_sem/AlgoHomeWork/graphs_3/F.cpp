//
// Created by topcr on 25.03.2024.
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

bool findCycle(vector<vector<int>>& g, vector<int>& used, int cur)
{
    used[cur] = 1;
    for(auto& to : g[cur])
    {
        if(used[to] == 2) continue;

        if(used[to] == 1) return true;

        if(findCycle(g, used, to)) return true;
    }
    used[cur] = 2;
    return false;
}
void makeOrder(vector<vector<int>>& g, vector<int>& order, vector<int>& used, int cur)
{
    used[cur] = 1;
    for(auto& to : g[cur])
    {
        if(used[to]) continue;
        makeOrder(g, order, used, to);
    }
    order.pb(cur);
}
void dfs(vector<vector<int>>& g, vector<int>& used, vector<int>& alph, string& s, int cur, int& ans)
{
    used[cur] = 1;
    ++alph[s[cur] - 'a'];
    if(g[cur].size() == 0)
    {
        ans = max(ans, *max_element(all(alph)));
    }
    else
    {
        for(auto& to : g[cur])
        {
            if(used[to]) continue;

            dfs(g, used, alph, s, to, ans);
        }
    }
    --alph[s[cur] - 'a'];
}
void solve()
{
    int n, m;
    cin >> n >> m;
    string s = " ", q;
    cin >> q;
    s = s + q;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
    }

    vector<int> used(n + 1);
    for(int v = 1; v < n + 1; ++v)
    {
        if(used[v] == 2) continue;

        if(findCycle(g, used, v))
        {
            cout << -1 << endl;
            return;
        }
    }

    used.assign(n + 1, 0);
    vector<int> order;
    for(int v = 1; v < n + 1; ++v)
    {
        if(used[v]) continue;

        makeOrder(g, order, used, v);
    }

    vector<vector<int>> dp(n + 1, vector<int> (26, 0));
    used.assign(n + 1, 0);
    int mx = 0;
    for(auto& v : order)
    {
        if(g[v].size())
        {
            for(auto& child : g[v])
            {
                for(int i = 0; i < 26; ++i)
                {
                    dp[v][i] = max(dp[v][i], dp[child][i]);
                    mx = max(mx, dp[v][i]);
                }
            }
        }
        dp[v][s[v] - 'a'] += 1;
        mx = max(mx, dp[v][s[v] - 'a']);
    }

    cout << mx << endl;
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