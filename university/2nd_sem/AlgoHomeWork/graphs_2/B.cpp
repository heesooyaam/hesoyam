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
bool x = false;
bool dfs(vector<unordered_set<int>>& g, vector<int>& used, vector<int>& ans, int cur)
{
    if(used[cur] == 2) return false;
    if(used[cur] == 1)
    {
        ans.pb(cur);
        return true;
    }
    used[cur] = 1;
    for(auto& to : g[cur])
    {
        if(dfs(g, used, ans, cur))
        {
            if(!x && cur != ans.front())
            {
                ans.pb(cur);
                return true;
            }
            else
            {
                x = true;
                return true;
            }
        }
    }
    used[cur] = 2;
    return false;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    if(m < 2)
    {
        cout << "NO" << endl;
        return;
    }
    vector<unordered_set<int>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].insert(to);
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
        reverse(all(ans));
        // ans.resize(find(next(ans.begin()), ans.end(), *ans.begin()) - ans.begin());
        print(ans);
    }

}
int32_t main()
{
    // freopen("cycle2.in", "r", stdin);
    // freopen("cycle2.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}