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

struct event
{
    event() = default;

    event(int idx, int pos, ll weight, char e)
    : idx(idx)
    , pos(pos)
    , weight(weight)
    , e(e) {}

    int pos, idx;
    ll weight;
    char e;

    bool operator<(const event& other) const
    {
        return (pos != other.pos) ? pos < other.pos : e < other.e;
    }
};
struct edge
{
    int from, to;
    ll weight;
    bool operator<(const edge& other) const
    {
        return weight < other.weight;
    }
};
struct vertex
{
    int idx;
    ll weight;
    bool operator<(const vertex& other) const
    {
        return weight < other.weight;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<event> events;
    vector<vertex> vertexes(n);
    for(int i = 0; i < n; ++i)
    {
        int l, r;
        ll weight;
        cin >> l >> r >> weight;
        vertexes[i] = {i, weight};
        events.eb(i, l, weight, 'o');
        events.eb(i, r + 1, weight, 'e');
    }

    sort(all(events));
    multiset<vertex> cost;
    vector<edge> edges;
    int r = 0;

    for(int i = 0; i < events.size(); ++i)
    {
        int l = i;
        while(r < events.size() && events[r].pos == events[i].pos)
        {
            if(events[i].e == 'o') cost.emplace(events[r].idx, events[r].weight);
            else cost.erase(cost.find({events[r].idx, events[r].weight})), ++l;
        }
        for(; l < r; ++l)
        {
            auto it = cost.lower_bound({0, events[l].weight});

            if(it != cost.end())
            {
                if(it->idx != events[l].idx)
                {
                    edges.eb(events[l].idx, it->idx, it->weight - events[i].weight);
                }
                else
                {
                    auto nxt = next(it);
                    if(nxt != cost.end() && nxt->idx != events[l].idx)
                    {
                        edges.eb(events[l].idx, nxt->idx, nxt->weight - events[i].weight);
                    }
                }
            }

            if(it->idx != it)

        }
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