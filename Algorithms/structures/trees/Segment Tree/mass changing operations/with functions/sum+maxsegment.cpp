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

template<class T>
class SegTree
{
public:
    struct Node
    {
        T pref = numeric_limits<T>::min(), suff = numeric_limits<T>::min(), sum = 0, mx = numeric_limits<T>::min();
        bool push = false;
    };
    explicit SegTree(size_t size)
            : n(size)
            , tree(n << 2, {0, 0, 0, 0})
    {}
    template<typename K>
    explicit SegTree(const vector<K>& vec)
            : n(vec.size())
            , tree(n << 2, Node())
    {
        build(0, 0, n, vec);
    }
    T getMaxSum() const
    {
        return tree[0].mx;
    }
    bool update(int l, int r, T val)
    {
        if(l >= r) return false;

        update(0, l, r, 0, n, val);
        return true;
    }
private:
    size_t n;
    vector<Node> tree;

    template<class K>
    void build(int idx, int l, int r, const vector<K>& vec)
    {
        if(l + 1 == r)
        {
            if(vec[l] > 0) tree[idx] = {vec[l], vec[l], vec[l], vec[l]};
            else tree[idx] = {0, 0, 0, 0};
            return;
        }
        int mid = (l + r) >> 1;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        recalc(idx);
    }
    void recalc(int idx)
    {
        int l_child = idx * 2 + 1, r_child = l_child + 1;

        tree[idx].pref = max(tree[l_child].pref, tree[l_child].sum + tree[r_child].pref);
        tree[idx].suff = max(tree[r_child].suff, tree[r_child].sum + tree[l_child].suff);
        tree[idx].sum = tree[l_child].sum + tree[r_child].sum;
        tree[idx].mx = max({tree[l_child].mx, tree[r_child].mx, tree[l_child].suff + tree[r_child].pref});
    }
    void setValue(int idx, T val, int len)
    {
        tree[idx].sum = val * len;
        tree[idx].mx = tree[idx].suff = tree[idx].pref = max((T) 0, val * len);
    }
    void push(int idx, int curL, int curR)
    {
        if(!tree[idx].push || curL + 1 == curR) return;

        int l_child = idx * 2 + 1, r_child = l_child + 1;
        int length = curR - curL;
        T val = tree[idx].sum / length;

        tree[l_child].push = tree[r_child].push = true;

        setValue(l_child, val, length / 2);
        setValue(r_child, val, length / 2 + length % 2);

        tree[idx].push = false;
    }

    void update(int idx, int l, int r, int curL, int curR, T val)
    {
        if(l >= r) return;

        if(curL == l && curR == r)
        {
            tree[idx].push = true;
            setValue(idx, val,r - l);
            return;
        }
        push(idx, curL, curR);
        int mid = (curL + curR) >> 1;

        update(idx * 2 + 1, l, min(mid, r), curL, mid, val);
        update(idx * 2 + 2, max(l, mid), r, mid, curR, val);
        recalc(idx);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    SegTree<ll> ST(n);
    for(int i = 0; i < m; ++i)
    {
        int l, r;
        ll val;
        cin >> l >> r >> val;
        ST.update(l, r, val);
        cout << ST.getMaxSum() << endl;
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