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
struct edge
{
    int u, v;
};
class DSU
{
public:

};
void dfs(vector<vector<int>>& g, vector<edge>& edges, int cur, int prev)
{

}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int v = 2; v < n + 1; ++v)
    {
        int parent;
        cin >> parent;
        g[parent].pb(v);
    }
    vector<edge> edges(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        edges[i] = {0, 0};
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