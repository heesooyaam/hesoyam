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

struct ZOTree
{
    struct Node
    {
        ll cnt1 = 0;
    };
    
    ZOTree(const vector<int>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    void build(const vector<int>& vec)
    {
        build(0, 0, n, vec);
    }
    int find(int k)
    {
        return find(0, 0, n, k + 1);
    }
    void update(int pos)
    {
        update(pos, 0, 0, n);
    }
private:
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b) const
    {
        return {.cnt1 = a.cnt1 + b.cnt1};
    }
    void build(int idx, int l, int r, const vector<int>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {.cnt1 = vec[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    int find(int idx, int l, int r, int k) const
    {        
        int mid = (l + r) / 2;
        if(l + 1 == r)
        {
            return l;
        }

        if(k - tree[idx * 2 + 1].cnt1 > 0)
        {
            k -= tree[idx * 2 + 1].cnt1;
            return find(idx * 2 + 2, mid, r, k);
        }
        else if(k - tree[idx * 2 + 1].cnt1 <= 0)
        {
            return find(idx * 2 + 1, l, mid, k);
        }

    }
    void update(int pos, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].cnt1 ^= 1;
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid) update(pos, idx * 2 + 1, l, mid);
        else update(pos, idx * 2 + 2, mid, r);

        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    input(vec);
    ZOTree ST = ZOTree(vec);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int pos;
            cin >> pos;
            ST.update(pos);
        }
        else
        {
            int k;
            cin >> k;
            cout << ST.find(k) << endl;
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