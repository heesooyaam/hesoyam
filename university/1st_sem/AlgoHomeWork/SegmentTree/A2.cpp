#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
struct SegTree 
{
    SegTree(const vector<int64_t>& vec)
    {
        tree.assign(vec.size() * 4, Node());
        build(vec);
    }
    void build(const vector<int64_t>& vec)
    {
        n = vec.size();
        build(0, 0, n, vec);
    }
    ll getMin(int64_t l, int64_t r) const
    {
        return getMin(0, l, r, 0, n).mn;
    }
private:
    struct Node
    {
        int64_t mn = INT_MAX;
    };
    int64_t n;
    vector<Node> tree;
    Node merge(const Node& a, const Node& b) const
    {
        return {.mn = min(a.mn, b.mn)};
    }
    Node getMin(int64_t pos, int64_t l, int64_t r, int64_t curL, int64_t curR) const
    {
        if(l >= r) return Node();
        else if(l == curL && r == curR)
        {
            return tree[pos];
        }

        int64_t mid = (curL + curR) >> 1;

        return merge(getMin(pos * 2 + 1, l, min(mid, r), curL, mid),
        getMin(pos * 2 + 2, max(mid, l), r, mid, curR));
    }
    void build(int64_t pos, int64_t l, int64_t r, const vector<int64_t>& vec)
    {
        if(l + 1 == r)
        {
            tree[pos].mn = vec[l];
            return;
        }
        int64_t mid = (l + r) / 2;
        build(pos * 2 + 1, l, mid, vec);
        build(pos * 2 + 2, mid, r, vec);
        tree[pos] = merge(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }
};
void solve()
{
    int n, m;
    cin >> n;
    vector<ll> vec(n);
    input(vec);
    cin >> m;
    SegTree ST = SegTree(vec);
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        cout << ST.getMin(l, r) << endl;
    }
}
int main()
{
    freopen("stupid_rmq.in", "r", stdin);
    freopen("stupid_rmq.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}