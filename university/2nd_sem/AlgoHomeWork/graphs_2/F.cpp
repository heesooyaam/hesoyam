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
int dfs(const vector<vector<int>>& g, vector<bool>& used, int cur)
{
    used[cur] = true;
    int cnt = 0;
    for(auto& to : g[cur])
    {
        if(to == cur)
        {
            ++cnt;
            continue;
        }
        if(used[to]) continue;

        cnt += dfs(g, used, to);
    }
    return 1 + cnt;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    if(m == 1)
    {
        cout << 0 << endl;
        return;
    }
    vector<vector<int>> g(n + 1);
    vector<int> hasPelmen(n + 1, 0);
    ll pelmeni = 0;
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
        if(from == to)
        {
            hasPelmen[from] = 1;
            ++pelmeni;
            continue;
        }
        g[to].pb(from);
    }
    int compCounter = 0;
    vector<bool> used(n + 1, false);
    vector<int> comp_size;

    for(int v = 1; v <= n; ++v)
    {
        if(used[v]) continue;

        comp_size.pb(dfs(g, used, v)); 
    }
    int cnt = 0;
    int cnt2 = 0;
    for(int i = 0; i < comp_size.size(); ++i)
    {
        if(comp_size[i] > 1) ++cnt;
        if(comp_size[i] > 2) ++cnt2; 
    }
    if(cnt > 1 || cnt == 0)
    {
        cout << 0 << endl;
        return;
    }
    ll ans = 0;
    for(int v = 1; v <= n; ++v)
    {
        ans += ((ll) g[v].size() - hasPelmen[v]) * ((ll) g[v].size() - hasPelmen[v] - 1) / 2;
    }
    ans += pelmeni * (m - pelmeni);
    ans += pelmeni * (pelmeni - 1) / 2;
    cout << ans << endl;
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