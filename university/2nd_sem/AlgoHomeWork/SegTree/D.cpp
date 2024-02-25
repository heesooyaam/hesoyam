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
template<class T>
int sign(T x) {
    return x > 0 ? 1 : x < 0 ? -1 : 0;
}
struct SegTree
{
    SegTree(vector<ll>& vec)
    : n(vec.size())
    , d(vec)
    , tree(n  * 4, Node())
    {}
    void update(int pos, ll val)
    {
        update(0, 0, n, pos, val);
    }
    ll getMax()
    {
        return max({tree[0].all, tree[0].pref, tree[0].suff}) + 1;
    }
private:
    int n;
    struct Node
    {
        ll pref, all, suff;
    };
    vector<Node> tree;
    vector<ll>& d;
    Node combine(const Node a, const Node b, int l, int r)
    {
        // first_a = vec[l + 1] - vec[l]
        // last_a = vec[mid] - vec[mid - 1]
        // first_b =  vec[mid + 1] - vec[mid]
        // last_b = vec[r] - vec[r - 1]
        int mid = (l + r) / 2;
        ll all = max(a.all, b.all);
        ll pref = a.pref;
        ll suff = b.suff;

        if(sign(d[mid - 1]) < sign(d[mid]) || d[mid - 1] == 0 || d[mid] == 0)
        {
            return {pref, all, suff};
        }

        if(a.all == mid - l)
        {     
            assert(a.all == a.pref && a.all == a.suff);
            pref = max(mid - l + 1 + b.pref, pref);
        }
        if(b.all == r - mid)
        {
            assert(b.all == b.pref && b.all == b.suff);
            suff = max(a.suff + r - mid + 1, suff);
        }
        all = max({all, a.suff + b.pref});
        return {pref, all, suff};

    }
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            if(d[l] != 0) tree[idx] = {1, 1, 1};
            else tree[idx] = {0, 0, 0};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2], l, r);
    }
    void update(int idx, int l, int r, int pos, ll val)
    {
        if(l + 1 == r)
        {
            if(d[l] != 0) tree[idx] = {1, 1, 1};
            else tree[idx] = {0, 0, 0};
            return;
        }
        int mid = (l + r) / 2;
        if(pos < mid) update(idx * 2 + 1, l, mid, pos, val);
        else update(idx * 2 + 2, mid, r, pos, val);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2], l, r);
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<ll> vec(n);
    input(vec);
    vector<ll> dif(n - 1);
    SegTree ST(dif);
    for(int i = 0; i < n - 1; ++i)
    {
        dif[i] = vec[i + 1] - vec[i];
    }
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int l, r;
        ll d;
        cin >> l >> r >> d;
        --l;
        --r;
        if(l != 0)
        {
            dif[l - 1] += d;
            ST.update(l - 1, d);
        }
        if(r != n - 1)
        {
            dif[r] -= d;
            ST.update(r, -d);
        }
        cout << ST.getMax() << endl;        
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