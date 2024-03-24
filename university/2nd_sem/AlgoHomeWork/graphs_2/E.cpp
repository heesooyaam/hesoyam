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
vector<vector<int>> check(vector<unordered_multiset<int>>& g)
{
    vector<vector<int>> e;
    auto add = [&e](int idx)->void 
    {
        if(e.back().size() < 2)
        {
            e.back().eb(idx);
        }
        else
        {
            e.eb(idx);
        }
    };
    for(int v = 1; v < g.size(); ++v)
    {
        if(g[v].size() % 2)
        {
            add(v);
        }
    }
}
void find(vector<unordered_multiset<int>>& g, vector<int>& ans, int cur)
{
    
    while(g[cur].size())
    {
        int to = *g[cur].begin();
        g[cur].erase(g[cur].begin());
        g[to].erase(g[to].find(cur));
        find(g, ans, cur);
    }
    ans.pb(cur);    
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<unordered_multiset<int>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].insert(to);
        g[to].insert(from);
    }
    vector<vector<int>> e = check(g);
    if(e.size() > 2 || (e.size() * 2 - e.back().size()) % 2)
    {
        cout << -1 << endl;
        return;
    }  
    if(e.size() == 0)
    {
        cout << -1 << endl;
        return;
    } 
    if(e.size() == 1)
    {
        vectror<int> ans
        find(g, ans, e.front().front());        
    }
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