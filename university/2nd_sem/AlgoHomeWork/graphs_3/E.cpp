//
// Created by topcr on 26.03.2024.
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
void makeOrder(vector<vector<int>>& g, vector<int>& order, vector<bool>& used, int cur)
{
    used[cur] = true;
    for(auto& to : g[cur])
    {
        if(used[to]) continue;

        makeOrder(g, order, used, to);
    }
    order.push_back(cur);
}
void makeComp(vector<vector<int>>& transp_g, vector<int>& compOfVertex, int cur, int compNumber)
{
    compOfVertex[cur] = compNumber;
    for(auto& to : transp_g[cur])
    {
        if(compOfVertex[to]) continue;

        makeComp(transp_g, compOfVertex, to, compNumber);
    }
}
void makeNewEdges(vector<unordered_set<int>>& condGraph, vector<pair<int, int>>& way, vector<bool>& used, int cur, int parent)
{
    used[cur] = true;
    int cnt = 0;
    for(const int& to : condGraph[cur])
    {
        if(used[to]) continue;
        ++cnt;
        makeNewEdges(condGraph, way, used, to, parent);
    }
    if(!cnt) way.eb(parent, cur);
}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1), transp_g(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        int x;
        cin >> x;
        g[i].pb(x);
        transp_g[x].pb(i);
    }
    vector<int> order;
    vector<bool> used(n + 1, false);
    for(int v = 1; v < n + 1; ++v)
    {
        if(used[v]) continue;
        makeOrder(g, order, used, v);
    }
    reverse(all(order));
    vector<int> compOfVertex(n + 1);
    int compNum = 0;
    vector<int> anyVertexOfComp = {-1};
    for(auto& v : order)
    {
        if(compOfVertex[v]) continue;
        anyVertexOfComp.pb(v);
        makeComp(transp_g, compOfVertex, v, ++compNum);
    }
    if(compNum == 1)
    {
        cout << 0 << endl;
        return;
    }
    vector<unordered_set<int>> condGraph(compNum + 1);
    vector<bool> hasParent(compNum + 1);
    for(int v = 1; v < n + 1; ++v)
    {
        for(auto& child : g[v])
        {
            if(compOfVertex[child] != compOfVertex[v]) hasParent[compOfVertex[child]] = true;
            condGraph[compOfVertex[v]].insert(compOfVertex[child]);
        }
    }
    used.assign(compNum + 1, false);
    vector<pair<int, int>> ways;
    for(int v = 1; v < compNum + 1; ++v)
    {
        if(hasParent[v] || used[v]) continue;

        makeNewEdges(condGraph, ways, used, v, v);
    }
    cout << ways.size() << endl;


    for(int i = 0; i < ways.size(); ++i)
    {
        cout << anyVertexOfComp[ways[i].ss] << ' ' << anyVertexOfComp[ways[(i + 1) % ways.size()].ff] << endl;
    }
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