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
#define print(x); for(auto& val : x){cout << val.sum << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n' 
#define int int64_t
  
template <typename T>
struct SumTree
{
    struct Node
    {
        T sum = 0;
    };
    
    SumTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    SumTree(size_t size)
    {
        n = size;
        tree.assign(n * 4, Node());
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    T getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n).sum;
    }
    void update(int pos, T val)
    {
        update(pos, val, 0, 0, n);
    }
    void Print() const
    {
        print(tree);
    }
private:
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b) const
    {
        return {.sum = a.sum + b.sum};
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {.sum = vec[l]};
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
            tree[idx].sum += val;
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
    SumTree<ll> ST(n);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll l, r, val;
            cin >> l >> r >> val;
            ST.update(l, val);
            if(r < n) ST.update(r, -1ll * val);
        }
        else if(type == 2)
        {
            int pos;
            cin >> pos;
            cout << ST.getSum(0, pos + 1) << endl;
        }
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