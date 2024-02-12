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

struct PairTree
{
    struct Node
    {
        bool found = false;
        map<int, int> pos;
    };
    
    PairTree(const vector<int>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, Node());
        build(vec);
    }
    PairTree(size_t size)
    {
        n = size;
        tree.assign(4 * n, Node());
    }
    void build(const vector<int>& vec)
    {
        build(0, 0, n, vec);
    }
    pair<int, int> hasPair(int l, int r)
    {
        Node res = hasPair(0, l, r, 0, n);
        if(!res.found) return {-1, -1};
        else return {res.pos.begin()->ss + 1, prev(res.pos.end())->ss + 1};
    }
private:
    int n;
    vector<Node> tree;
    Node combine(const Node a, const Node b) const
    {
        if(a.found == true) return a;
        if(b.found == true) return b;
        Node ab;
        for(auto& [val, position] : a.pos)
        {
            ab.pos[val] = position;
        }
        for(auto& [val, position] : b.pos)
        {
            ab.pos[val] = position;
        }

        if(ab.pos.size() > 1) ab.found = true;

        return ab;
    }
    void build(int idx, int l, int r, const vector<int>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].pos[vec[l]] = l;
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    Node hasPair(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return Node();
        if(l == curL && r == curR) return tree[idx];
        
        int mid = (curL + curR) / 2;

        return combine(hasPair(idx * 2 + 1, l, min(r, mid), curL, mid), hasPair(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    input(vec);
    int m;
    cin >> m;
    PairTree ST(vec);
    for(int i = 0; i < m; ++i)
    {
        int l, r;
        cin >> l >> r;
        auto ans = ST.hasPair(l - 1, r);
        cout << ans.ff << ' ' << ans.ss << endl;
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}