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
struct SegTree
{
    struct Node
    {
        ll sum = 0;
    };
    SegTree(vector<ll>& vec)
    {
        this->n = vec.size();
        t.assign(n << 2, {});
        build(vec);
    }
    void build(const vector<ll>& vec)
    {
        build(0, 0, vec.size(), vec);
    }
    ll getSum(ll l, ll r) 
    {
        if(l >= r) return 0;
        
        return (getSum(0, l, r, 0, n)).sum;
    }
    void update(ll pos, ll val)
    {
        update(pos, val, 0, 0, n);
    }
private:
    ll n;
    vector<Node> t;
    void build(ll ind, ll l, ll r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            t[ind] = {.sum = vec[l]};
            return; 
        }
        ll mid = (l + r) >> 1;
        build((ind << 1) + 1, l, mid, vec);
        build((ind << 1) + 2, mid, r, vec);
        t[ind] = combine(t[(ind << 1) + 1], t[(ind << 1) + 2]);
    }
    Node getSum(ll idx, ll l, ll r, ll curL, ll curR)
    {
        if(l >= r) return {.sum = 0};
        if(l == curL && r == curR) return t[idx];
        ll mid = (curL + curR) >> 1;
        return combine(getSum((idx << 1) + 1, l, min(r, mid), curL, mid),
        getSum((idx << 1) + 2, max(l, mid), r, mid, curR));
    }
    void update(ll pos, ll val, ll idx, ll l, ll r)
    {
        if(l + 1 == r)
        {
            t[idx].sum = val;
            return;
        }
 
        ll mid = (l + r) >> 1;
 
        if(pos < mid) update(pos, val, (idx << 1) + 1, l, mid);
        else update(pos, val, (idx << 1) + 2, mid, r);
 
        t[idx] = combine(t[(idx << 1) + 1], t[(idx << 1) + 2]);
    }
    Node combine(const Node& a, const Node& b) const
    {
        return {.sum = (a.sum + b.sum)};
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> a(n), b(n);
    input(a);
    input(b);
    for(int i = 0; i < n - 1; ++i)
    {
        ll x; cin >> x;
    }
    SegTree water = SegTree(a);
    SegTree wizzard = SegTree(b);
    for(int i = 0; i < q; ++i)
    {
        ll p, a, b, c;
        cin >> p >> a >> b >> c;
        --p;
        water.update(p, a);
        wizzard.update(p, b);
        cout << min(water.getSum(0, n), wizzard.getSum(0, n)) << endl;
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    ll ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}