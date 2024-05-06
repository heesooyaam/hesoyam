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
int log(int n)
{
    for(int i = 30; i >= 0; --i)
    {
        if(n & (1 << i)) return i + 1;
    }
    return -1;
}
void solve()
{
    int k;
    cin >> k;
    int logn = log(k);
    vector<vector<int>> parent(1 << (logn + 1), vector<int>(logn + 1, 1));
    vector<int> depth(1 << (logn + 1), 0);
//    unordered_map<ull, unordered_map<ull, ull>> parent;
//    unordered_map<ull, int> depth;
    auto add = [&](ull a, ull parA)
    {
        depth[a] = depth[parA] + 1;
        parent[a][0] = parA;
        for(int i = 1; i <= logn; ++i)
        {
            parent[a][i] = parent[parent[a][i - 1]][i - 1];
        }
    };
    auto ancestor = [&](ull child, int dist)
    {
        for(int i = logn; i >= 0; --i)
        {
            if((dist >> i) & 1)
            {
                child = parent[child][i];
            }
        }
        return child;
    };
    auto LCA = [&](int a, int b)
    {
//        cerr << "###################\n" << a << ' ' << b << " on start of LCA" << endl;
        if(depth[a] != depth[b])
        {
            int& mx = (depth[a] < depth[b] ? b : a);
            mx = ancestor(mx, depth[mx] - depth[a + b - mx]);
        }

        if(a == b) return a;


        for(int i = logn; i >= 0; --i)
        {
            if(parent[a][i] != parent[b][i])
            {
                a = parent[a][i];
                b = parent[b][i];
            }
        }

//        cerr << "###################" << endl;
        return parent[a][0];
    };
    for(int i = 0; i < k; ++i)
    {
        string type;
        cin >> type;
        int a, b;
        cin >> a >> b;
        if(type[0] == 'A')
        {
            add(b, a);
        }
        else
        {
            cout << LCA(a, b) << endl;
        }
    }
}
int32_t main()
{
    // freopen("lca.in", "r", stdin);
    // freopen("lca.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}