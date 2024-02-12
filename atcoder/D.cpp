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
// #define endl '\n'   
    int n;
ll dxtr(const vector<vector<pair<int, int>>>& g, vector<ll>& dist)
{
    set<pair<ll, int>> st = {{0, 1}};
    vector<bool> used(n + 1);
    used[1] = true;
    int cur = 1;
    while(true)
    {
        if(st.empty() || used[n]) break;
        cur = st.begin()->ss;
        used[cur] = true;
        st.erase(st.begin());
        for(auto& [to, range] : g[cur])
        {
            if(!used[to])
            {
                if(dist[to] > dist[cur] + range)
                {
                    st.erase({dist[to], to});
                    st.insert({dist[cur] + range, to});
                    dist[to] = dist[cur] + range;
                }
            }
        }
        // cout << "11" << endl;
    }
    return dist[n];
}
void solve()
{
    cin >> n;
    vector<vector<pair<int, int>>> graph(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        ll a, b, x;
        cin >> a >> b >> x;
        graph[i + 1].eb(i + 2, a);
        graph[i + 1].eb(x, b);
    }
    vector<ll> dist(n + 1, 1e15);
    dist[1] = 0;
    ll ans = dxtr(graph, dist);
    cout << ans << endl;

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