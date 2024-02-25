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
ll ans = 0;
bool dfs(vector<vector<int>>& g, string& st, vector<bool>& used, vector<bool>& good, int cur, int prev)
{
    used[cur] = true;
    for(auto& to : g[cur])
    {
        if(to == prev || st[to] == 'P') continue;

        good[cur] = dfs(g, st, used, good, to, cur);
    }
}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i < n; ++i)
    {
        int vertex;
        cin >> vertex;
        g[i + 1].pb(vertex);
        g[vertex].pb(i + 1);
    }
    string st = " ";
    string q;
    cin >> q;
    st += q;
    int root;
    for(int i = 1; i < n + 1; ++i)
    {
        if(g[i].size() == 1)
        {
            root = i;
            break;
        }
    }
    vector<bool> used(n + 1, false);
    for(int i = 1; i < n + 1; ++i)
    {
        if(used[i] || st[i] != 'C') continue;
        dfs(g, st, used, i, -1);
    }
    cout << ans << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}