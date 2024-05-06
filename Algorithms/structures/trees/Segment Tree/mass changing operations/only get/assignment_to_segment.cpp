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
template <typename T>   
struct AssignmentTree
{
    AssignmentTree(size_t size)
    : n(size)
    {
        tree.assign(n << 2, Node());
    }
    AssignmentTree(const vector<T>& vec)
    : n(vec.size())
    {
        tree.assign(n << 2, Node());
        build(vec);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    T get(int pos)
    {
        return get(pos, 0, 0, n).ss;
    }
    void update(int l, int r, T val)
    {
        ++operations;
        update(l, r, val, 0, 0, n);
    }

private:
    struct Node
    {
        pair<int, T> val = {0, 0};
    };
    int n;
    int operations = 0;
    vector<Node> tree;
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].val.ss = vec[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
    }
    pair<int, T> get(int pos, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            return tree[idx].val;
        }

        int mid = (l + r) / 2;

        if(pos < mid) return max(tree[idx].val, get(pos, idx * 2 + 1, l, mid));
        else return max(tree[idx].val, get(pos, idx * 2 + 2, mid, r));
    }
    void update(int l, int r, T val, int idx, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].val = {operations, val};
            return;
        }

        int mid = (curL + curR) / 2;

        update(l, min(r, mid), val, idx * 2 + 1, curL, mid);
        update(max(l, mid), r, val, idx * 2 + 2, mid, curR);
    }
    
};
void solve()
{
    int n, m;
    cin >> n >> m;
    AssignmentTree<ll> ST(n);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll l, r, val;
            cin >> l >> r >> val;
            ST.update(l, r, val);
        }
        else if(type == 2)
        {
            int pos;
            cin >> pos;
            cout << ST.get(pos) << endl;
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