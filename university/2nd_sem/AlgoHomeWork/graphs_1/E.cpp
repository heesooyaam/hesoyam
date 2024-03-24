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
int k;
int ans;
bool dfs(vector<vector<int>>& g, vector<int>& in, int cur, int prev, vector<int>& ans)
{

    for(auto& to : g[cur])
    {
        if(to == prev) continue;

        if(in[to] == -1)
        {
            in[to] = in[cur] + 1;
            if(dfs(g, in, to, cur, ans))
            {
                ans.pb(cur);
                return true;
            }
        }
        else
        {
            if(in[cur] - in[to] >= k)
            {
                ans.pb(to);
                ans.pb(cur);
                return true;
            }
        }
    }
    return false;
}

void solve()
{
    int n, m;
    cin >> n >> m >> k;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < m ; ++i)
    {
        int to, from;
        cin >> from >> to;
        g[to].pb(from);
        g[from].pb(to);
    }
    vector<int> in(n + 1, -1);
    in[1] = 0;
    vector<int> ans;
    dfs(g, in, 1, -1, ans);
    ans.resize(find(next(ans.begin()), ans.end(), ans.front()) - ans.begin());
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