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
struct SumTree
{
    struct Node
    {
        T sum = 0;
    };
    
    SumTree(const vector<T>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    void build(const vector<T>& vec)
    {
        build(0, 0, n, vec);
    }
    T getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n).sum;
    }
    void update(int pos, T val)
    {
        update(pos, val, 0, 0, n);
    }
private:
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b) const
    {
        return {.sum = a.sum + b.sum};
    }
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {.sum = vec[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    Node getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node();
        if(l == curL && r == curR) return tree[idx];
        
        int mid = (curL + curR) / 2;

        return combine(getSum(idx * 2 + 1, l, min(r, mid), curL, mid), getSum(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
    void update(int pos, T val, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = val;
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid) update(pos, val, idx * 2 + 1, l, mid);
        else update(pos, val, idx * 2 + 2, mid, r);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> b(2 * n);
    input(b);
    vector<int> watched(2 * n, 0);
    SumTree<int> ST(watched);
    vector<pair<int, int>> seg(n + 1, {-1, -1});
    for(int i = 0; i < 2 * n; ++i)
    {
        if(seg[b[i]].ff == -1)
        {
            seg[b[i]].ff = i;
        }
        else seg[b[i]].ss = i + 1;
    }
    vector<int> ans(n + 1, 0);
    for(int i = 0; i < 2 * n; ++i)
    {
        if(seg[b[i]].ff == i) continue;
        // cout << "!!" << endl;
        // cout << "seg - " << b[i];
        ans[b[i]] = ST.getSum(seg[b[i]].ff, i);
        ST.update(seg[b[i]].ff, 1);
    }
    for(int i = 1; i <= n; ++i)
    {
        cout << ans[i] << ' ';
    }
    cout << endl;
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