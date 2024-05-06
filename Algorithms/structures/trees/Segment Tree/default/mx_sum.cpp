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
template <typename T>
struct MaxSumTree
{
    struct Node
    {
        ll pref = 0; 
        ll suff = 0;
        ll sum = 0; 
        ll mx = 0;
    };
    
    MaxSumTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    T getSum(int l, int r)
    {
        return max(getSum(0, l, r, 0, n).mx, (T) 0);
    }
    void update(int pos, T val)
    {
        update(pos, val, 0, 0, n);
    }
private:
    int n;
    vector<Node> tree;
    Node combine(const Node l, const Node r) const
    {
        Node newSeg = {.pref = max(l.pref, l.sum + r.pref), .suff = max(r.suff, l.suff + r.sum), .sum = l.sum + r.sum, .mx = (ll) -1e15};
        newSeg.mx = max({r.pref + l.suff, l.mx, r.mx});
        return newSeg; 
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].pref = tree[idx].suff = max(vec[l], (T) 0);
            tree[idx].sum = vec[l];
            tree[idx].mx = vec[l];
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    Node getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node();
        if(l == curL && r == curR) return tree[idx];
        
        int mid = (curL + curR) / 2;

        return combine(getSum(idx * 2 + 1, l, min(r, mid), curL, mid), getSum(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
    void update(int pos, T val, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = tree[idx].pref = tree[idx].suff = val;
            tree[idx].mx = max(val, (T) 0);
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid) update(pos, val, idx * 2 + 1, l, mid);
        else update(pos, val, idx * 2 + 2, mid, r);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    MaxSumTree<ll> ST(vec);
    cout << ST.getSum(0, n) << endl;
    for(int i = 0; i < m; ++i)
    {
        ll pos, val;
        cin >> pos >> val;
        ST.update(pos, val);
        cout << ST.getSum(0, n) << endl; 
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