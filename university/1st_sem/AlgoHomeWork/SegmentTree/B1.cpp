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
struct event
{
    int64_t pos;
    char side;
    int64_t mn;
    event(int64_t x, char y, int64_t& z)
    : pos(x)
    , side(y)
    , mn(z)
    {}
    bool operator <(const event& other) const
    {
        return (pos != other.pos) ? pos < other.pos : (side != other.side) ? side > other.side : true;
    }
};
struct request
{
    int64_t l, r, mn;
    request(int64_t l, int64_t r, int64_t& mn)
    : l(l)
    , r(r)
    , mn(mn)
    {}
    request() = default;
};
void solve()
{
    int64_t n, q;
    cin >> n >> q;
    vector<int64_t> vec(n, INT_MIN);
    vector<request> requests(q);
    vector<event> events;
    for(int64_t i = 0; i < q; ++i)
    {
        int64_t l, r, mn;
        cin >> l >> r >> mn;
        requests[i] = request(l - 1, r, mn);
        events.eb(event(l - 1, 'l', mn));
        events.eb(event(r, 'r', mn));
    }
    sort(all(events));
    int64_t position = events[0].pos;
    multiset<int64_t> mins;
    mins.insert(INT_MIN);
    int64_t j = 0;
    for(int64_t i = 0; i < events.size();)
    {
        while(j < position && j < n) vec[j++] = *prev(mins.end());
        while(i < events.size() && events[i].pos == position)
        {
            int s = mins.size();
            if(events[i].side == 'l')
            {
                mins.insert(events[i].mn);
            }
            else
            {
                mins.erase(mins.find(events[i].mn));
            }
            ++i;
        }
        if(i < events.size()) position = events[i].pos;
    }
    // while(j < n) vec[j++] = *prev(mins.end());
    SegTree ST = SegTree(vec);
    bool ok = true;
    for(auto& request : requests)
    {
        ok = request.mn == ST.getMin(request.l, request.r);
        if(!ok) break;
    }
    if(!ok) cout << "inconsistent\n";
    else
    {
        cout << "consistent\n";
        print(vec);
    }
}
int32_t main()
{
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int64_t t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}