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

// Дан взвешенный граф N < 10^5 вершин, M < 2 * 10^5 ребер.
// Найдите количество минимальных остовных деревьев при условии,
// что для каждого натурального числа в графе есть не больше 10 ребер с таким весом.
const ll MOD = 1'000'000'007;
ll C(ll n, ll k)
{
    ll res = 1;
    ll mx = max(k, n - k);
    ll mn = min(k, n - k);
    for(ll i = n; i > mx; --i)
    {
        res *= i;
    }
    for(ll i = 1; i <= mn; ++i)
    {
        res /= i;
    }
    return res;
}
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
class Edge
{
public:
    int from, to;
    ll weight;
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for(int i = 0; i < m; ++i)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
    sort(all(edges));
    DSU dsu(n, 1);
    vector<bool> deleted(m);
    ll ans = 1;
    vector<int> unionNumber;
    auto count = [&](ll uni, int l)
    {
        ll res = 0;
        for(int i = 0; i < unionNumber.size(); ++i)
        {
            if(unionNumber[i] == uni)
            {
                deleted[i + l] = true;
                ++res;
            }
        }
        return res;
    };
    for(int i = 0; i < m; )
    {
        int l = i;
        int r = i + 1;
        ll curAvailable = 0;
        ll taken = 0;
        while(r < m && edges[r].weight == edges[r - 1].weight) ++r;
        for(int j = l; j < r; ++j)
        {
            if(dsu.areInTheSameUnion(edges[j].from, edges[j].to))
            {
                deleted[j] = true;
            }
        }
        for(int mask = 0; mask < (1 << (r - l)); ++mask)
        {
            DSU curDsu(r - l);
            int submask = mask;
            for(int bit = 0; bit < r - l; ++bit)
            {
                if(mask & (1 << bit))
                {
                    submask ^= (1 << bit);
                    break;
                }
            }
            
        }
//        ans *= C(curAvailable, taken);
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