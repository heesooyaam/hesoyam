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
struct edge {
    int from, to;
    ll weight;
    bool operator < (const edge& other) const
    {
        return this->weight < other.weight;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<edge> edges(m);
    for(int i = 0; i < m; ++i)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
    sort(all(edges));
    DSU dsu(n, 1);
    vector<bool> used(m);
    ll ans = 0;
    for(int i = 0; i < m; )
    {
        int l = i;
        int r = i + 1;
        while(r < m && edges[r].weight == edges[r - 1].weight) ++r;
        for(int j = l; j < r; ++j)
        {
            if(dsu.areInTheSameUnion(edges[j].from, edges[j].to))
            {
                used[j] = true;
            }
        }
        for(int j = l; j < r; ++j)
        {
            if(used[j]) continue;

            if(dsu.areInTheSameUnion(edges[j].from, edges[j].to))
            {
                ++ans;
            }
            else dsu.unite(edges[j].from, edges[j].to);
        }
        i = r;
    }
    cout << ans << endl;
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