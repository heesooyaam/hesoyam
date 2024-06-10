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
class Tree
{
public:
    explicit Tree(const vector<ll>& a, const vector<ll>& b, const ll MOD = 1'000'000'007)
            : n(a.size())
            , MOD(MOD)
            , tree(n << 2, Node())
    {
        build(0, 0, n, a, b);
    }
    void update(int l, int r, ll x, int type)
    {
        array<ll, 2> d = {0, 0};
        d[type - 1] = x;
        return update(0, l, r, 0, n, d);
    }
    ll get(int l, int r)
    {
        return get(0, l, r, 0, n);
    }
private:
    size_t n;
    struct Node
    {
        Node()
                : sum({0, 0, 0})
                , d({0, 0})
                , push(false) {}
        array<ll, 3> sum;
        array<ll, 2> d;
        bool push = false;
    };
    const ll MOD;
    array<int, 2> childs;
    vector<Node> tree;

    void merge(int idx)
    {
        assert(!tree[idx].push);
        childs = {idx * 2 + 1, idx * 2 + 2};
        tree[idx].sum = {0, 0, 0};
        for(auto&& child : childs)
        {
            tree[idx].sum[0] += tree[child].sum[0];
            tree[idx].sum[1] += tree[child].sum[1];
            tree[idx].sum[2] += tree[child].sum[2];
        }
        for(int i : {0, 1, 2})
        {
            tree[idx].sum[i] %= MOD;
        }
    }
    void recalc(int idx, const array<ll, 2>& d, ll length)
    {
        tree[idx].sum[2] +=
                (d[1] * tree[idx].sum[0]) % MOD
                + (d[0] * tree[idx].sum[1]) % MOD
                + (((d[1] * d[0]) % MOD) * length) % MOD;
        tree[idx].sum[2] %= MOD;

        tree[idx].sum[0] += (d[0] * length) % MOD;
        tree[idx].sum[0] %= MOD;

        tree[idx].sum[1] += (d[1] * length) % MOD;
        tree[idx].sum[1] %= MOD;

        tree[idx].d[0] += d[0];
        tree[idx].d[0] %= MOD;
        tree[idx].d[1] += d[1];
        tree[idx].d[1] %= MOD;

        tree[idx].push = true;
    }

    void push(int idx, int curL, int curR)
    {
        if(!tree[idx].push || curL + 1 == curR) return;

        int l_child = idx * 2 + 1, r_child = idx * 2 + 2;
        int mid = (curL + curR) >> 1;

        // left child:
        recalc(l_child, tree[idx].d, mid - curL);

        // right child:
        recalc(r_child, tree[idx].d, curR - mid);

        tree[idx].push = false;
        tree[idx].d = {0, 0};
    }
    void build(int idx, int l, int r, const vector<ll>& a, const vector<ll>& b)
    {
        if(l + 1 == r)
        {
            tree[idx].sum[0] = a[l];
            tree[idx].sum[1] = b[l];
            tree[idx].sum[2] = (a[l] * b[l]) % MOD;
            return;
        }

        int mid = (l + r) >> 1;

        build(idx * 2 + 1, l, mid, a, b);
        build(idx * 2 + 2, mid, r, a, b);

        merge(idx);
    }

    void update(int idx, int l, int r, int curL, int curR, const array<ll, 2>& d)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            return recalc(idx, d, curR - curL);
        }

        int mid = (curL + curR) >> 1;

        push(idx, curL, curR);

        update(idx * 2 + 1, l, min(mid, r), curL, mid, d);
        update(idx * 2 + 2, max(l, mid), r, mid, curR, d);

        merge(idx);
    }

    ll get(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;

        push(idx, curL, curR);

        if(l == curL && r == curR)
        {
            return tree[idx].sum[2];
        }

        int mid = (curL + curR) >> 1;


        return (get(idx * 2 + 1, l, min(mid, r), curL, mid)
                + get(idx * 2 + 2, max(l, mid), r, mid, curR)) % MOD;
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> a(n), b(n);
    input(a);
    input(b);
    Tree ST(a, b, 998244353);
    for(int i = 0; i < q; ++i)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if(type < 3)
        {
            ll x;
            cin >> x;
            ST.update(l - 1, r, x, type);
        }
        else
        {
            ll res = ST.get(l - 1, r);
            cout << res << endl;
        }
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}