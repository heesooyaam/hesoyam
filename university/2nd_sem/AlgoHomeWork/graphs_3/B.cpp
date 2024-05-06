//
// Created by topcr on 29.03.2024.
//
#include <bits/stdc++.h>
#include <atomic>
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
vector<ll> precomp(15000, 0);
vector<ll> pref(15000, 0);
//#define int int64_t
// 1 <-> 2 <-> 3
// path: 1->2->3->2->1

namespace stt
{
    class mutex
    {
    public:
        void lock()
        {
            bool flag = true;
            while(!free.compare_exchange_weak(flag, false)) {}
        }
        void unlock()
        {
            free = true;
        }
    private:
        std::atomic<bool> free;
    };
}
struct edge
{
    int to;
    ll weight;
};

void sort(vector<vector<edge>>& g, vector<bool>& used, vector<int>& order, int cur)
{
    used[cur] = true;
    for(auto& [to, weight] : g[cur])
    {
        if(used[to]) continue;

        sort(g, used, order, to);
    }
    order.pb(cur);
}
void makeComp(vector<vector<edge>>& g, vector<int>& compOfVertex, int cur, const int compNum)
{
    compOfVertex[cur] = compNum;
    for(auto& [to, weight] : g[cur])
    {
        if(compOfVertex[to]) continue;

        makeComp(g, compOfVertex, to, compNum);
    }
}
// s - 1 - 2 - 3 ...
// s - AP
// s -
// 10**8 - (0 + 1 + 2 + 3 + 4 + 5 + ...) >= 0
// 10**8 - (n - 1) * n / 2 >= 0
ll countProfit(ll w)
{
    ll l, r;
    l = 1; r = 15000;
    while(l + 1 < r)
    {
        ll mid = (l + r) >> 1;
        if(w - mid * (mid - 1) / 2 >= 0)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    return  w * l - pref[l];
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n + 1);
    vector<vector<edge>> transp_g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        ll weight;
        cin >> from >> to >> weight;
        g[from].eb(to, weight);
        transp_g[to].eb(from, weight);
    }
    int start;
    cin >> start;
    vector<bool> used(n + 1);
    vector<int> order;
    for(int v = 1; v < n + 1; ++v)
    {
        if(used[v]) continue;
        sort(g, used, order, v);
    }
    reverse(all(order));
    vector<int> compOfVertex(n + 1);
    int compNum = 0;
    for(auto& v : order)
    {
        if(compOfVertex[v]) continue;

        makeComp(transp_g, compOfVertex, v, ++compNum);
    }
    vector<vector<edge>> condG(compNum + 1);
    vector<ll> compWeight(compNum + 1);
    for(int v = 1; v < n + 1; ++v)
    {
        int fromComp = compOfVertex[v];
        for(auto& [to, weight] : g[v])
        {
            int toComp = compOfVertex[to];

            if(toComp == fromComp)
            {
                compWeight[fromComp] += countProfit(weight);
                continue;
            }

            condG[fromComp].eb(toComp, weight);
        }
    }
    used.assign(compNum + 1, false);
    order.clear();
    for(int v = 1; v < compNum + 1; ++v)
    {
        if(used[v]) continue;

        sort(condG, used, order, v);
    }
//    reverse(all(order));
    vector<ll> dp(compNum + 1);
    for(auto& cssV : order)
    {
        if(condG[cssV].empty())
        {
            dp[cssV] = compWeight[cssV];
        }
        else
        {
            for(auto& [child, weight] : condG[cssV])
            {
                dp[cssV] = max(dp[cssV], dp[child] + weight);
            }
            dp[cssV] += compWeight[cssV];
        }
    }
    cout << dp[compOfVertex[start]] << endl;


}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
    for(ll i = 2; i < precomp.size(); ++i)
    {
        precomp[i] = precomp[i - 1] + i - 1;
    }
    for(int i = 1; i < precomp.size(); ++i)
    {
        pref[i] = pref[i - 1] + precomp[i];
    }
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}