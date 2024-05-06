#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = double;
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
    int x, y;
};
void solve()
{
    int n;
    cin >> n;
    vector<point> points(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }
    auto len = [](const point& a, const point& b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    };
    int counter = n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    vector<int> minEdgeTo(n, numeric_limits<int>::max());
    vector<bool> used(n);
    q.emplace(0, 0);
    ld ans = 0;
    while(counter)
    {
        auto cur = q.top().ss;
        auto d = q.top().ff;
        q.pop();

        if(used[cur]) continue;
        used[cur] = true;
        --counter;

        ans += sqrt(abs(ld(d)));

        for(int to = 0; to < n; ++to)
        {
            if(used[to]) continue;

            int curLen = len(points[cur], points[to]);

            if(minEdgeTo[to] > curLen)
            {
                minEdgeTo[to] = curLen;
                q.emplace(minEdgeTo[to], to);
            }
        }
    }
    cout << fixed << setprecision(3) << ans << endl;

}
int32_t main()
{
    // freopen("unionday.in", "r", stdin);
    // freopen("unionday.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}