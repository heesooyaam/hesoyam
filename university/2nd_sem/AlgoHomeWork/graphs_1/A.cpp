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
bool dfs(vector<vector<int>>& g, vector<int>& used, vector<int>& ans, int cur)
{
    used[cur] = 1;
    for(auto& to : g[cur])
    {
        if(used[to] == 2) continue;
        if(used[to] == 0)
        {
            if(dfs(g, used, ans, to))
            {
                ans.pb(cur);
                return true;
            }
        }
        else if(used[to] == 1)
        {
            ans.pb(to);
            ans.pb(cur);
            return true;
        }
    }
    used[cur] = 2;
    return false;
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
        g[from].eb(to);
    }
    vector<int> used(n + 1, 0);
    vector<int> ans;
    bool found = false;
    for(int v = 1; v <= n && !found; ++v)
    {
        if(used[v] == 2) continue;

        found = dfs(g, used, ans, v);
    }
    if(!found)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
        ans.resize(find(next(ans.begin()), ans.end(), *ans.begin()) - ans.begin());
        reverse(all(ans));
        print(ans);
    }

}
int32_t main()
{
    freopen("cycle2.in", "r", stdin);
    freopen("cycle2.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}