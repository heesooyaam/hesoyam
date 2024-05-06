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

void solve()
{
    int n;
    cin >> n;
    vector<vector<ll>> w(n + 1, vector<ll> (n + 1, 0));
    for(int i = 1; i < n + 1; ++i)
    {
        for(int j = 1; j < n + 1; ++j)
        {
            cin >> w[i][j];
        }
    }
    vector<ll> step(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> step[i];
    }
    step.eb(0);
    reverse(all(step));
    vector<vector<vector<ll>>> dist(2, vector<vector<ll>> (n + 1, vector<ll> (n + 1, numeric_limits<int>::max())));
    vector<ll> ans = {0};
    for(int i = 1, q = 0; i < n; ++i, q ^= 1)
    {
        for(int u = 1; u < n + 1; ++u)
        {
            dist[q ^ 1][u][step[i]] = min(dist[q ^ 1][u][step[i]] == numeric_limits<int>::max() ? , w[u][step[i]]);
            dist[q ^ 1][step[i]][u] = min(dist[q ^ 1][u][step[i]], w[step[i]][u]);
        }
        ans.eb(0);
        for(int u = 1; u < n + 1; ++u)
        {
            for(int v = 1; v < n + 1; ++v)
            {
                if(u == v)
                {
                    dist[q][u][v] = 0;
                    continue;
                }

                dist[q][u][v] = min(dist[q ^ 1][u][v], dist[q ^ 1][u][step[i]] + dist[q ^ 1][step[i]][v]);
                ans.back() += dist[q][u][v];
            }
        }
    }
    reverse(all(ans));
    print(ans);
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