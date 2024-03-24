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
#define int int64_t
struct Fenwick
{
    explicit Fenwick(const vector<ll>& vec)
    : n(vec.size())
    , tree(n, 0)
    {
        build(vec);
    }
    explicit Fenwick(int l)
    : n(l)
    , tree(l, 0)
    {}
    ll getSum(int l, int r)
    {
        return getPref(r) - ((l) ? getPref(l - 1) : 0);
    }
    void update(int pos, ll val)
    {
        for(int i = pos; i < n; i = g(i))
        {
            tree[i] += val;
        }
    }
private:
    int n;
    vector<ll> tree;
    int f(int idx)
    {
        return idx & (idx + 1);
    }
    int g(int idx)
    {
        return idx | (idx + 1);
    }
    void build(const vector<ll>& vec)
    {
        vector<ll> pref(vec.size(), 0);
        for(int i = 0; i < n; ++i)
        {
            pref[i] = vec[i] + ((i) ? pref[i - 1] : 0);
        }
        auto getSum = [&pref](int l, int r)->ll
        {
            return pref[r] - ((l) ? pref[l - 1] : 0);
        };
        for(int i = n - 1; i >= 0; --i)
        {
            tree[i] = getSum(f(i), i);
        }
    }
    ll getPref(int idx)
    {
        ll ans = 0;
        for(int i = idx; i >= 0; i = f(i) - 1)
        {
            ans += tree[i];
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
        if(type)
        {
            ll pos, val;
            cin >> pos >> val;
            --pos;
            Tree.update(pos, val - vec[pos]);
            vec[pos] = val;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << Tree.getSum(l - 1, r - 1) << endl;
        }
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