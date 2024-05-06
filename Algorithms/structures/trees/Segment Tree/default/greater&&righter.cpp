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
struct MaxTree
{
    MaxTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    int greaterThan(T x, int l)
    {
        return greaterThan(0, l, n, 0, n, x);
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

    int greaterThan(int idx, int l, int r, int curL, int curR, T x)
    {
        if(l >= r) return -1;

        if(l + 1 == r && curR == r && curL == l)
        {
            // cout << "tree[" << idx << "].mx = " << tree[idx].mx << ", x = " << x << endl;
            if(tree[idx].mx < x) return -1;
            else return l;
        }

        int mid = (curR + curL) / 2;

        int returned = -1;

        if(l < mid && tree[idx * 2 + 1].mx >= x)
        {
            returned = greaterThan(idx * 2 + 1, l, min(r, mid), curL, mid, x);
        }
        if(returned == -1) return greaterThan(idx * 2 + 2, max(l, mid), r, mid, curR, x);
        else return returned;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    MaxTree<ll> ST(vec);
    // cout << "vector: "; print(vec);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll pos, val;
            cin >> pos >> val;
            ST.update(pos, val);
            // vec[pos] = val;
            // cout << "updated: ";
            // print(vec);
        }
        else if(type == 2)
        {
            int x, l;
            cin >> x >> l;
            cout << ST.greaterThan(x, l) << endl;
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