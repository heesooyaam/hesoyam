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
class DSU
{
public:
    explicit DSU(size_t size, int indexation = 0)
    : n(size)
    , unionsCounter(n)
    , unionSize(n + indexation, 1)
    , parent(n + indexation, 0)
    {
        for(int i = indexation; i < n + indexation; ++i)
        {
            parent[i] = i;
        }
    }
    int getParent(int v)
    {
        if(parent[v] == v) return v;

        parent[v] = getParent(parent[v]);

        return parent[v];
    }
    void unite(int a, int b)
    {
        a = getParent(a);
        b = getParent(b);
        if(a == b) return;
        --unionsCounter;
        if(unionSize[a] > unionSize[b])
        {
            swap(a, b);
        }
        unionSize[b] += unionSize[a];
        parent[a] = b;
    }
    bool areInTheSameUnion(int a, int b)
    {
        return getParent(a) == getParent(b);
    }
    size_t unionsAmount() const
    {
        return unionsCounter;
    }
private:
    size_t n;
    size_t unionsCounter;
    vector<int> unionSize;
    vector<int> parent;
};

int dfs(const vector<vector<pair<pair<ll, ll>, int>>>& g, vector<bool>& used, int cur)
{
    used[cur] = true;
    int weight = 1;
    for(const auto& [cost, to] : g[cur])
    {
        if(used[to]) continue;

        weight += dfs(g, used, to);
    }
    return weight;
}

bool cmp(const pair<pair<ll, ll>, pair<int, int>>& a, const pair<pair<ll, ll>, pair<int, int>>& b)
{
    return a.ff < b.ff;
}

struct mstEdge
{
    ll cost;
    int edgeNumber, to;
    bool operator<(const mstEdge& other) const
    {
        return mp(cost, mp(edgeNumber, to)) < mp(other.cost, mp(other.edgeNumber, other.to));
    }
};

pair<ll, pair<int, pair<int, int>>> FindMaxEdge(vector<set<mstEdge>>& MST, int cur, int prevEdge, int head)
{
    for(const auto& [cost, edgeNumber, to] : MST[cur])
    {
        if(prevEdge == edgeNumber) continue;

        if(to == head)
        {
            return {cost, {edgeNumber, {cur, to}}};
        }

        auto childEdge = FindMaxEdge(MST, to, edgeNumber, head);

        if(childEdge.ff == numeric_limits<ll>::min()) continue;

        if(childEdge.ff > cost)
        {
            return childEdge;
        }
        else
        {
            return {cost, {edgeNumber, {cur, to}}};
        }
    }
    return {numeric_limits<ll>::min(), {-1, {-1, -1}}};
}
void solve()
{
    int n, m;
    cin >> n >> m;
    ll gold, silver;
    cin >> gold >> silver;
    vector<vector<pair<pair<ll, ll>, int>>> graph(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        ll g, s;
        cin >> g >> s;
        if(from == to) continue;
        if(from > to) swap(from, to);
        graph[from].eb(mp(g, s), to);
//        graph[to].eb(mp(g, s), from);
    }

    {
        vector<bool> used(n + 1);
        if(n != dfs(graph, used, 1))
        {
            cout << -1 << endl;
            return;
        }
    }

    int ptr = -1;
    vector<pair<pair<ll, ll>, pair<int, int>>> edges(m);
    for(int from = 1; from < n + 1; ++from)
    {
        for(const auto& [cost, to] : graph[from])
        {
            edges[++ptr] = mp(cost, mp(from, to));
        }
    }

    sort(all(edges), cmp);

    vector<set<mstEdge>> MST(n + 1);
    ll ans = numeric_limits<ll>::max();
    ll curG = edges.front().ff.ff;
    multiset<ll, greater<>> silvers;
    DSU dsu(n, 1);

    int i = 0;
    while(i < edges.size())
    {
        while(i < edges.size() && edges[i].ff.ff == curG)
        {
            int from = edges[i].ss.ff, to = edges[i].ss.ss;
            ll cost = edges[i].ff.ss;

            MST[from].insert({cost, i, to});
            MST[to].insert({cost, i, from});

            if(dsu.areInTheSameUnion(from, to))
            {
                auto mxEdge = FindMaxEdge(MST, from, -1, from);
                if(mxEdge.ff > cost)
                {
                    MST[mxEdge.ss.ss.ff].erase({mxEdge.ff, mxEdge.ss.ff, mxEdge.ss.ss.ss});
                    MST[mxEdge.ss.ss.ss].erase({mxEdge.ff, mxEdge.ss.ff, mxEdge.ss.ss.ff});
                    silvers.erase(silvers.find(mxEdge.ff));
                    silvers.insert(cost);
                }
                else
                {
                    MST[from].erase({cost, i, to});
                    MST[to].erase({cost, i, from});
                }
            }
            else
            {
                dsu.unite(from, to);
                silvers.insert(cost);
            }
            ++i;
        }

        if(dsu.unionsAmount() == 1) ans = min(ans, curG * gold + *silvers.begin() * silver);

        if(i < edges.size()) curG = edges[i].ff.ff;
    }
    cout << (ans == numeric_limits<ll>::max() ? 0 : ans) << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}