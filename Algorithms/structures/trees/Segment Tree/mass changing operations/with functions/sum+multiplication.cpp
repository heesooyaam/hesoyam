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
ll MOD = 1'000'000'007;
template<typename T>
struct SumMultTree
{
    SumMultTree(size_t size, T val = 1)
    : n(size)
    , def(val)
    {
        tree.assign(n << 2, Node());
        build();
    }
    SumMultTree(const vector<T>& vec)
    : n(vec.size())
    {
        tree.assign(n << 2, Node());
        build(vec);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    void build()
    {
        build(0, 0, n);
    }
    void update(int l, int r, T m)
    {
        update(l, r, m, 0, 0, n);
    }
    ll getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
private:
    int n;
    struct Node
    {
        ll dif = 1;
        ll sum = 0;
    };
    ll def;
    vector<Node> tree;
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = vec[l];
            return;
        }
        
        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = def;
            return;
        }
        
        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void update(int l, int r, T m, int idx, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].dif *= m;
            tree[idx].dif %= MOD;
            tree[idx].sum *= m;
            tree[idx].sum %= MOD;
            return;
        }

        int mid = (curL + curR) / 2;

        update(l, min(r, mid), m, idx * 2 + 1, curL, mid);
        update(max(mid, l), r, m, idx * 2 + 2, mid, curR);

        tree[idx].sum = (((tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum) % MOD) * tree[idx].dif) % MOD;
    }
    ll getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;

        if(l == curL && r == curR)
        {
            return tree[idx].sum;
        }
        
        int mid = (curL + curR) / 2;

        return (((getSum(idx * 2 + 1, l, min(r, mid), curL, mid) + getSum(idx * 2 + 2, max(l, mid), r, mid, curR)) % MOD) * tree[idx].dif) % MOD;
    }
    
};
void solve()
{
    int n, m;
    cin >> n >> m;
    SumMultTree<ll> ST(n);
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