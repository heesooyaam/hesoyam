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
    DSU(int size)
    : n(size)
    , unionSize(n, 1)
    , unionsCounter(size)
    , parent(size, 0)
    {
        for(int i = 0; i < n; ++i)
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
    int unionsAmount() const
    {
        return unionsCounter;
    }
private:
    int n;
    int unionsCounter;
    vector<int> unionSize;
    vector<int> parent;
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n + 1);
    for(int i = 0; i < m; ++i)
    {
        string s;
        cin >> s;
        if(s.front() == 'g')
        {
            int a, b;
            cin >> a >> b;
            cout << (dsu.getParent(a) == dsu.getParent(b) ? "YES" : "NO") << endl;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            dsu.unite(a, b);
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