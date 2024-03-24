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

struct Fenwick
{
    // explicit Fenwick(const vector<ll>& vec)
    // : n(vec.size())
    // , tree(n, vector<vector<ll>> (n, vector<ll> (n)))
    // {
    //     build(vec);
    // }
    explicit Fenwick(int l)
    : n(l + 1)
    , tree(l + 1, vector<vector<ll>> (n + 1, vector<ll> (n + 1)))
    {}
    ll getSum(int x1, int y1, int z1, int x2, int y2, int z2)
    {
        return getPref(x2, y2, z2) - getPref(x2, y1, z2) - getPref(x1, y2, z2) + getPref(x1, y1, z2) - getPref(x2, y2, z1) + getPref(x2, y1, z1) + getPref(x1, y2, x1) - getPref(x1, y1, z1);
    }
    void update(int x, int y, int z, ll val)
    {
        for(int i = x; i < n; i = g(i))
        {
            for(int j = y; j < n; j = g(j))
            {
                for(int k = z; k < n; k = g(k))
                {
                    tree[i][j][k] += val;
                }
            }
        }
    }
private:
    int n;
    vector<vector<vector<ll>>> tree;
    int f(int idx)
    {
        return idx & (idx + 1);
    }
    int g(int idx)
    {
        return idx | (idx + 1);
    }
    // void build(const vector<ll>& vec)
    // {
    //     vector<ll> pref(vec.size(), 0);
    //     for(int i = 0; i < n; ++i)
    //     {
    //         pref[i] = vec[i] + ((i) ? pref[i - 1] : 0);
    //     }
    //     auto getSum = [&pref](int l, int r)->ll
    //     {
    //         return pref[r] - ((l) ? pref[l - 1] : 0);
    //     };
    //     for(int i = n - 1; i >= 0; --i)
    //     {
    //         tree[i] = getSum(f(i), i);
    //     }
    // }
    ll getPref(int x, int y, int z)
    {
        ll ans = 0;
        for(int i = x; i >= 0; i = f(i) - 1)
        {
            for(int j = y; j >= 0; j = f(j) - 1)
            {
                for(int k = z; k >= 0; k = f(k) - 1)
                {
                    ans += tree[i][j][k];
                }
            }
        }
        return ans;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    Fenwick Tree(vec);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll pos, val;
            cin >> pos >> val;
            --pos;
            Tree.update(pos, val - vec[pos]);
            vec[pos] = val;
        }
        else if(type == 2)
        {
            int l, r;
            cin >> l >> r;
            cout << Tree.getSum(l - 1, r - 1) << endl;
        }
        else break;
    }
}
int32_t main()
{
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}