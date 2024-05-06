//
// Created by topcr on 02.04.2024.
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
class slowDSU
{
public:
    explicit slowDSU(size_t size, size_t indexation = 0)
    : parent(size + indexation, 0)
    , n(size)
    , unionsCounter(size)
    , unionSize(n + indexation, 1)
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
        unionSize[b] += unionSize[a];
        parent[a] = b;
    }
    size_t unionsAmount() const
    {
        return unionsCounter;
    }
    vector<int> parent;
private:
    size_t n;
    size_t unionsCounter;
    vector<int> unionSize;
};
void solve()
{
    int n, q;
    cin >> n >> q;
    slowDSU dsu(n, 1);
    slowDSU lastIndex(n, 1);
    for(int i = 0; i < q; ++i)
    {
        int type, x, y;
        cin >> type >> x >> y;
        if(x > y) swap(x, y);
        if(type == 1)
        {
            dsu.unite(x, y);
            if(x == y - 1)
            {
                lastIndex.unite(x, y);
            }
        }
        else if(type == 2)
        {
            int idx = upper_bound(all(lastIndex.parent), lastIndex.getParent(x)) - lastIndex.parent.begin();
            while(idx <= y)
            {
                dsu.unite(x, idx);
                lastIndex.unite(x, idx);
                idx = upper_bound(all(lastIndex.parent), lastIndex.getParent(x)) - lastIndex.parent.begin();
            }
        }
        else
        {
            cout << ((dsu.areInTheSameUnion(x, y)) ? "YES\n" : "NO\n");
        }
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