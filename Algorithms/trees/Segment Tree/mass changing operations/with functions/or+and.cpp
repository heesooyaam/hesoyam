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
struct BitOrAndTree
{
    explicit BitOrAndTree(size_t size, T def = 0)
    : n(size)
    , def(def)
    {
        tree.assign(n * 4, {.OR = 0, .AND = def});
    }
    explicit BitOrAndTree(const vector<T>& vec)
    : n(vec.size())
    {
        tree.assign(n * 4, Node());
        build(0, 0, n, vec);
    }
    void update(int l, int r, T val)
    {
        update(0, l, r, val, 0, n);
    }
    T getAND(int l, int r)
    {
        return getAND(0, l, r, 0, n);
    }
private:
    struct Node
    {
        T OR = 0;
        T AND = 0;
    };
    int n;
    T def;
    vector<Node> tree;
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].AND = vec[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx].AND = tree[idx * 2 + 1].AND & tree[idx * 2 + 2].AND;
    }   
    void update(int idx, int l, int r, T val, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].OR |= val;
            tree[idx].AND |= val;
            return;
        }

        int mid = (curL + curR) / 2;

        update(idx * 2 + 1, l, min(r, mid), val, curL, mid);
        update(idx * 2 + 2, max(l, mid), r, val, mid, curR);

        tree[idx].AND = (tree[idx * 2 + 1].AND & tree[idx * 2 + 2].AND) | tree[idx].OR;
    }

    T getAND(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return ~(T(0));

        if(l == curL && r == curR)
        {
            return tree[idx].AND;
        }

        int mid = (curL + curR) / 2;

        return (getAND(idx * 2 + 1, l, min(r, mid), curL, mid) & getAND(idx * 2 + 2, max(l, mid), r, mid, curR)) | tree[idx].OR;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    BitOrAndTree<int> ST(n);
    for(int i = 0; i < m; ++i)
    {
        int type, l, r;
        cin >> type;
        if(type == 1)
        {
            int val;
            cin >> l >> r >> val;
            ST.update(l, r, val);
        }
        else
        {
            cin >> l >> r;
            cout << ST.getAND(l, r) << endl;
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