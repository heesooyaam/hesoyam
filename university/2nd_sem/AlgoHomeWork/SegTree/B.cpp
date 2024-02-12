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
struct MinAddTree
{
    MinAddTree(size_t size)
    : n(size)
    , def({.dif = 0, .mn = 0})
    {
        tree.assign(n << 2, def);
    }
    MinAddTree(const vector<T>& vec)
    : n(vec.size())
    {
        tree.assign(n << 2, Node());
        build(vec);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    T getMin(int l, int r)
    {
        return getMin(0, l, r, 0, n);
    }
    void update(int l, int r, T val)
    {
        update(l, r, val, 0, 0, n);
    }

private:
    struct Node
    {
        T dif = 0;
        T mn = (sizeof(T) == 32) ? INT_MAX : LLONG_MAX;
    };
    int n;
    const Node def;
    vector<Node> tree;
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

        tree[idx].mn = min(tree[idx * 2 + 1].mn, tree[idx * 2 + 2].mn);
    }
    void update(int l, int r, T val, int idx, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].dif += val;
            tree[idx].mn += val;
            return;
        }

        int mid = (curL + curR) / 2;

        update(l, min(r, mid), val, idx * 2 + 1, curL, mid);
        update(max(l, mid), r, val, idx * 2 + 2, mid, curR);

        tree[idx].mn = min(tree[idx * 2 + 1].mn, tree[idx * 2 + 2].mn) + tree[idx].dif;
    }

    T getMin(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node().mn;

        if(l == curL && r == curR)
        {
            return tree[idx].mn;
        }

        int mid = (curL + curR) / 2;

        return min(
        getMin(idx * 2 + 1, l, min(r, mid), curL, mid),
        getMin(idx * 2 + 2, max(l, mid), r, mid, curR)) + tree[idx].dif;
    }

};
void solve()
{
    int n;
    cin >> n;
    vector<ll> vec(n);
    input(vec);
    MinAddTree<ll> ST(vec);
    int m;
    cin >> m;
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        ++r;
        string s;
        getline(cin, s);
        if(s.size() != 0)
        {
            ll val = stoll(s);
            if(l < r)
            {
                ST.update(l, r, val);
            }
            else
            {
                ST.update(l, n, val);
                ST.update(0, r, val);
            }
        }
        else
        {
            if(l < r)
            {
                cout << ST.getMin(l, r) << endl;
            }
            else
            {
                cout << min(ST.getMin(l, n), ST.getMin(0, r)) << endl;
            }
        }
    }

}
int32_t main()
{
    // freopen("b.in", "r", stdin);
    // freopen("b.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}