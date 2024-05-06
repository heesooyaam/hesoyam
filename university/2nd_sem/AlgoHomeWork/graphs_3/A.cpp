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
const ll MOD = 1'000'000'007;
struct MinCnt
{
    ll mn;
    ll cnt;
};
void makeOrder(vector<vector<int>>& g, vector<int>& order, vector<bool>& used, int cur)
{
    used[cur] = true;
    for(auto& to : g[cur])
    {
        if(used[to]) continue;

        makeOrder(g, order, used, to);
    }
    order.pb(cur);
}
void countComp(vector<vector<int>>& transp_g, vector<MinCnt>& compCost, vector<ll>& cost, vector<bool>& used, int cur, int compNumber)
{
    used[cur] = true;
    if(compCost[compNumber].mn == cost[cur])
    {
        ++compCost[compNumber].cnt;
    }
    else if(compCost[compNumber].mn > cost[cur])
    {
        compCost[compNumber] =  {cost[cur], 1};
    }

    for(auto& to : transp_g[cur])
    {
        if(used[to]) continue;

        countComp(transp_g, compCost, cost, used, to, compNumber);
    }
}
void solve()
{
    int n;
    cin >> n;
    vector<ll> cost(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> cost[i];
    }
    int m;
    cin >> m;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> transp_g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
        transp_g[to].pb(from);
    }
    vector<int> order;
    vector<bool> used(n + 1, false);
    for (int v = 1; v < n + 1; ++v)
    {
        if(!used[v]) makeOrder(g, order, used, v);
    }
    reverse(all(order));
    vector<MinCnt> compCost;
    used.assign(n + 1, false);
    for (auto& v : order)
    {
        if(used[v]) continue;

        compCost.eb(numeric_limits<ll>::max(), 0);
        countComp(transp_g, compCost, cost, used, v, compCost.size() - 1);
    }

    ll ans = 0;
    ll variants = 1;
    for(auto& [val, cnt] : compCost)
    {
        ans += val;
        variants *= cnt;
        variants %= MOD;
    }
    cout << ans << ' ' << variants << endl;
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