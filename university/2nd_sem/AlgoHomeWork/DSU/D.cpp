//
// Created by touch on 02.04.2024.
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
struct edge
{
    int from, to;
};
void solve()
{
    int n;
    cin >> n;
    DSU dsu(n + 1);
    vector<vector<int>> g(n + 1);
    vector<edge> edgesToBeDeleted;
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        if(dsu.areInTheSameUnion(from, to))
        {
            edgesToBeDeleted.eb(from, to);
        }
        else
        {
            dsu.unite(from, to);
        }
    }
    vector<edge> newEdges;

    for(int from = 1; from <= n && dsu.unionsAmount(); ++from)
    {
        for(int to = from + 1; to <= n && dsu.unionsAmount(); ++to)
        {
            if(dsu.areInTheSameUnion(from, to)) continue;

            newEdges.eb(from, to);
            dsu.unite(from, to);
        }
    }
    assert(newEdges.size() == edgesToBeDeleted.size());
    cout << newEdges.size() << endl;
    for(int i = 0; i < newEdges.size(); ++i)
    {
        cout << edgesToBeDeleted[i].from << ' ' << edgesToBeDeleted[i].to << ' '
        << newEdges[i].from << ' ' << newEdges[i].to << endl;
    }

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