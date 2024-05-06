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
struct point
{
    ll x, y;
    bool operator<(const point& other) const
    {
        return true;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<point> points(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }
    auto len = [](const point& a, const point& b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    };
    int counter = n;
    set<pair<ll, int>> st;
    vector<ll> minEdgeTo(n + 1, numeric_limits<ll>::max());
    vector<bool> used(n + 1);
    st.insert({0, 1});
    ld ans = 0;
    vector<pair<int, int>> edges;
    vector<int> prev(n + 1);
    while(counter)
    {
        auto cur = st.begin()->ss;
        auto d = st.begin()->ff;

        st.erase(st.begin());
        used[cur] = true;
        --counter;
        edges.eb(cur, prev[cur]);

        ans += sqrtl(abs(ld(d)));

        for(int to = 1; to < n + 1; ++to)
        {
            if(used[to]) continue;

            ll curLen = len(points[cur], points[to]);

            if(minEdgeTo[to] > curLen)
            {
                if(minEdgeTo[to] != numeric_limits<ll>::max()) st.erase({minEdgeTo[to], to});

                minEdgeTo[to] = curLen;
                st.insert({minEdgeTo[to], to});
                prev[to] = cur;
            }
        }
    }
    cout << fixed << setprecision(7) << ans << endl;
    cout << n - 1 << endl;
    for(int i = 1; i < edges.size(); ++i)
    {
        cout << edges[i].ff << ' ' << edges[i].ss << endl;
    }
}
int32_t main()
{
    // freopen("connect.in", "r", stdin);
    // freopen("connect.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}