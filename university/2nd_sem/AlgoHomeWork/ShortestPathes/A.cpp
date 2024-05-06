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
struct edge
{
    int to;
    ll cost;
};
struct djkstra
{
    ll len;
    int from, to;
    bool operator<(const djkstra& other) const
    {
        return !(this->len < other.len);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        ll cost;
        cin >> cost;
        g[from].eb(to, cost);
        g[to].eb(from, cost);
    }
    vector<ll> dist(n + 1, numeric_limits<ll>::max());
    vector<ll> prev(n + 1, -1);
    vector<bool> used(n + 1, false);
    priority_queue<djkstra> path; path.push({0, -1, 1});
    while(!path.empty())
    {
        auto choice = path.top();
        path.pop();
        int cur = choice.to;
        if(used[cur]) continue;

        ll len = choice.len;
        prev[cur] = choice.from;
        used[cur] = true;
        for(const auto& [to, cost] : g[cur])
        {
            if(dist[to] > dist[cur] + cost)
            {
                dist[to] = dist[cur] + cost;
                path.push({dist[to], cur, to});
            }
        }
    }
    if(dist[n] == numeric_limits<ll>::max())
    {
        cout << -1 << endl;
        return;
    }
    int cur = n;
    vector<int> answer;
    while(cur != -1)
    {
        answer.eb(cur);
        cur = prev[cur];
    }
    reverse(all(answer));
    print(answer);
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}