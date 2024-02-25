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
template<typename T> 
struct MinTree
{
    MinTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
        // cerr << "SEGTREE WAS CREATED" << endl;
    }
    T getMin(int l, int r)
    {
        return getMin(0, l, r, 0, n).mn;
    }
    void update(int pos, T val)
    {
        update(pos, val, 0, 0, n);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
private:
    struct Node{
        ll mn = 1e15;
    };
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b)
    {
        return {.mn = min(a.mn, b.mn)};
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].mn = vec[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    void update(int pos, T val, int idx, int l, int r)
    {
        if(l == r - 1)
        {
            tree[idx].mn = val;
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid) update(pos, val, idx * 2 + 1, l, mid);
        else update(pos, val, idx * 2 + 2, mid, r);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }

    Node getMin(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node();
        if(l == curL && r == curR) return tree[idx];

        int mid = (curR + curL) / 2;

        return combine(getMin(idx * 2 + 1, l, min(r, mid), curL, mid),
        getMin(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
};
template<typename T> 
struct MaxTree
{
    MaxTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
        // cerr << "SEGTREE WAS CREATED" << endl;
    }
    T getMax(int l, int r)
    {
        return getMax(0, l, r, 0, n).mx;
    }
    void update(int pos, T val)
    {
        update(pos, val, 0, 0, n);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
private:
    struct Node{
        ll mx = -1e15;
    };
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b)
    {
        return {.mx = max(a.mx, b.mx)};
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].mx = vec[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    void update(int pos, T val, int idx, int l, int r)
    {
        if(l == r - 1)
        {
            tree[idx].mx = val;
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid) update(pos, val, idx * 2 + 1, l, mid);
        else update(pos, val, idx * 2 + 2, mid, r);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }

    Node getMax(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node();
        if(l == curL && r == curR) return tree[idx];

        int mid = (curR + curL) / 2;

        return combine(getMax(idx * 2 + 1, l, min(r, mid), curL, mid),
        getMax(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> l(n);
    vector<ll> r(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i];
    }
    MaxTree<ll> L(l);
    MinTree<ll> R(r);
    for(int i = 0; i < m; ++i)
    {
        char type;
        cin >> type;
        if(type == '?')
        {
            ll left, right;
            cin >> left >> right;
            // ll mn = R.getMin(left - 1, right);
            // ll mx = L.getMax(left - 1, right);
            cout << max(0ll, R.getMin(left - 1, right) - L.getMax(left - 1, right) + 1) << endl;
        }
        else
        {
            ll idx, left, right;
            cin >> idx >> left >> right;
            L.update(idx - 1, left);
            R.update(idx - 1, right);
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