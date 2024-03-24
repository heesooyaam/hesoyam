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

class Tree
{
public:
    Tree(const vector<ll>& vec)
    : n(vec.size())
    , tree(n << 2, Node())
    {
        build(0, 0, n, vec);
    }
    Tree(int size_)
    : n(size_)
    , tree(n << 2, Node())
    {}

    void update(int l, int r, ll val)
    {
        update(0, l, r, 0, n, val);
    }

    ll getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
    
private:
    struct Node
    {
        ll sum = 0;
        ll val = 0;
        bool push = false;
    };
    int n;
    vector<Node> tree;
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {vec[l], 0, false};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void push(int idx, int l, int r)
    {
        if(!tree[idx].push || l + 1 == r) return;

        int l_child = idx * 2 + 1, r_child = l_child + 1;

        int mid = (l + r) / 2;

        tree[l_child] = {tree[idx].val * (mid - l), tree[idx].val, true};
        tree[r_child] = {tree[idx].val * (r - mid), tree[idx].val, true};

        tree[idx].val = 0;
        tree[idx].push = false;
    }
    void update(int idx, int l, int r, int curL, int curR, ll val)
    {
        if(l >= r) return;


        if(l == curL && r == curR)
        {
            tree[idx] = {val * (r - l), val, true};
            return;
        }

        int mid = (curL + curR) >> 1;

        push(idx, curL, curR);

        update(idx * 2 + 1, l, min(mid, r), curL, mid, val);
        update(idx * 2 + 2, max(mid, l), r, mid, curR, val);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    ll getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;

        if(l == curL && r == curR)
        {
            return tree[idx].sum;
        }
        
        int mid = (curL + curR) / 2;

        push(idx, curL, curR);

        return getSum(idx * 2 + 1, l, min(r, mid), curL, mid) + getSum(idx * 2 + 2, max(l, mid), r, mid, curR);
    }
};


void solve()
{
    int n, q;
    cin >> n >> q;
    Tree ST(n);
    while(q--)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            ST.update(l, r, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << ST.getSum(l, r) << endl;
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