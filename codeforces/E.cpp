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
int n, m;  
void dfs(vector<vector<int>>& graf, vector<int>& value, vector<int>& dist, vector<bool>& d, int cur, int prev)
{
    // used[cur] = true;
    if(cur == n)
    {
        dist[cur] = 1;
        return;
    }
    for(int to : graf[cur])
    {
        if(prev == to || dist[to] == -2) continue;

        if(value[to] == value[cur])
        {
            if(dist[to] != -1)
            {

                if(dist[cur] != -1)
                {
                    dist[cur] = max(dist[to], dist[cur]);
                }
                else dist[cur] = dist[to];
            }
            else
            {
                dfs(graf, value, dist, d, to, cur);
                if(dist[to] == -2) continue;

                if(dist[cur] != -1) dist[cur] = max(dist[to], dist[cur]);
                else dist[cur] = dist[to];
            }
        }

        if(dist[to] != -1)
        {

            if(dist[cur] != -1)
            {
                dist[cur] = max(dist[to] + 1, dist[cur]);
            }
            else dist[cur] = dist[to] + 1;
        }
        else
        {
            dfs(graf, value, dist, d, to, cur);
            if(dist[to] == -2) continue;

            if(dist[cur] != -1) dist[cur] = max(dist[to] + 1, dist[cur]);
            else dist[cur] = dist[to] + 1;
        }
    }
    if(dist[cur] == -1 && !d[cur]) dist[cur] = -2;

}
void solve()
{
    cin >> n >> m;
    vector<int> value(n + 1);
    for(int i = 1; i < n + 1; ++i) cin >> value[i];
    vector<bool> d(n + 1, false);
    vector<vector<int>> graf(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to; cin >> from >> to;
        if(value[from] > value[to])
        {
            graf[to].eb(from);
        }
        else if(value[from] < value[to])
        {
            graf[from].eb(to);
        }
        else
        {
            d[to] = d[from] = true;
            graf[to].eb(from);
            graf[from].eb(to);
        }
    }
    vector<int> dist(n + 1, -1);
    dfs(graf, value, dist, d, 1, -1);
    if(dist[1] != -2) cout << dist[1] << endl;
    else cout << 0 << endl;
    // cout << (dist[1] == -2) ? 0 : dist[1] << endl;
    
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