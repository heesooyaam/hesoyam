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
        cerr << "SEGTREE WAS CREATED" << endl;
    }
    pair<T, int> getMin(int l, int r)
    {
        auto result = getMin(0, l, r, 0, n);
        return mp(result.mn, result.cnt);
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
        int cnt = 1;
    };
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b)
    {
        if(a.mn == b.mn)
        {
            return {.mn = a.mn, .cnt = a.cnt + b.cnt};
        }
        else if(a.mn < b.mn)
        {
            return a;
        }
        else return b;
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].mn = vec[l];
            tree[idx].cnt = 1;
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
            tree[idx].cnt = 1;
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
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    MinTree<ll> ST(vec);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            ll pos, val;
            cin >> pos >> val;
            ST.update(pos, val);
        }
        else if(type == 2)
        {
            int l, r;
            cin >> l >> r;
            auto ans = ST.getMin(l, r);
            cout << ans.ff << ' ' << ans.ss << endl;
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