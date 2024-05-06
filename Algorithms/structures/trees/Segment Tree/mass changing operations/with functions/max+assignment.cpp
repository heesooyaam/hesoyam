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
struct MaxAssignTree
{
    MaxAssignTree(size_t size, T def = (T) 0)
    : n(size)
    , def(def)
    {
        tree.assign(n * 4, {.clear = true, .val = 0, .mx = def});
    }
    MaxAssignTree(const vector<T>& vec)
    : n(vec.size())
    {
        tree.assign(n * 4, Node());
        build(0, 0, n, vec);
    }
    void update(int l, int r, T val)
    {
        update(0, l, r, 0, n, val);
    }
    T getMax(int l, int r)
    {
        return getMax(0, l, r, 0, n);
    }
private:

    struct Node
    {
        bool clear = true;
        T val = 0;
        T mx = (sizeof(T) == 32) ? INT_MAX / 2 : LLONG_MAX / 2;
    };

    int n;
    T def;
    vector<Node> tree;
     
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
        tree[idx].mx = max(tree[idx * 2 + 1].mx, tree[idx * 2 + 2].mx);
    }
    void push(int idx, int L, int R)
    {
        if(tree[idx].clear || L + 1 == R) return;
        
        int l = idx * 2 + 1, r = idx * 2 + 2;

        tree[l].val = tree[r].val = tree[l].mx = tree[r].mx = tree[idx].mx = tree[idx].val;
        
        tree[idx].clear = true;
        tree[l].clear = tree[r].clear = false;
    }
    
    void update(int idx, int l, int r, int curL, int curR, T val)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            push(idx, curL, curR);

            tree[idx].val = val;
            tree[idx].mx = val;
            tree[idx].clear = false;
            return;
        } 

        int mid = (curL + curR) / 2;
        
        push(idx, curL, curR);

        update(idx * 2 + 1, l, max(r, mid), curL, mid, val);
        update(idx * 2 + 2, max(l, mid), r, mid, curR, val);

        tree[idx].mx = (tree[idx].clear) ? max(tree[idx * 2 + 1].mx, tree[idx * 2 + 2].mx) : tree[idx].val;
    }
    T getMax(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return (sizeof(T) == 32) ? INT_MAX / 5 : LLONG_MAX / 5;
        
        if(!tree[idx].clear) return tree[idx].mx;

        if(l == curL && r == curR) return tree[idx].mx;

        int mid = (curL + curR) / 2;

        return max(getMax(idx * 2 + 1, l, max(r, mid), curL, mid), getMax(idx * 2 + 2, max(l, mid), r, mid, curR));
    }

};
void solve()
{
    int n, m;
    cin >> n >> m;
    MaxAssignTree<ll> ST(n);
    for(int i = 0; i < m; ++i)
    {
        int type, l, r;
        cin >> type;
        if(type == 1)
        {
            ll val;
            cin >> l >> r >> val;
            ST.update(l, r, val);
        }
        else
        {
            cin >> l >> r;
            cout << ST.getMax(l, r) << endl;
        }
    }
}
int32_t main()
{
    // freopen("rsq.in", "r", stdin);
    // freopen("rsq.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}