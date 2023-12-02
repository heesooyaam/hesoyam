#include <bits/stdc++.h>
#include <chrono>
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
class TimeMeasurer
{
private:
    const std::chrono::steady_clock::time_point begin;
public:
    TimeMeasurer()
    : begin(std::chrono::steady_clock::now())
    {}
    
    ~TimeMeasurer()
    {
        auto t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin);
        cout << "Elapsed time: ";
        cout << t.count() << '\n';
    }
};

inline ll countDist(pair<ll, ll>& a, pair<ll, ll>& b)
{
    return (a.ff - b.ff) * (a.ff - b.ff) + (a.ss - b.ss) * (a.ss - b.ss);
}  
void solve()
{
    int x, y;
    cin >> x >> y;
    int n; cin >> n;
    //TimeMeasurer timer = TimeMeasurer();
    vector<pair<ll, ll>> clothes(n + 1);
    for(int i = 0; i < n; ++i)
    {
        cin >> clothes[i].ff >> clothes[i].ss;
    }
    ll always = 0;
    clothes[n] = {x, y};
    vector<vector<ll>> dist(n + 1, vector<ll> (n + 1));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            dist[i][j] = countDist(clothes[i], clothes[j]);
        }
    }
    for(int i = 0; i < n; ++i) always += dist[i][n];
    vector<ll> dp(1 << (n), INT_MAX);
    dp[0] = 0;
    vector<pair<ll, ll>> prev(1 << n);
    for(int mask = 0; mask < (1 << n) - 1; ++mask)
    {
        for(int from = 0; from < n; ++from)
        {
            if((mask >> from) & 1) continue;
            for(int to = from + 1; to <= n; ++to)
            {
                if((to != n && ((mask >> to) & 1))) continue;

                if(to != n)
                {
                    if(dp[mask + (1 << from) + (1 << to)] > dp[mask] + dist[from][to])
                    {
                        dp[mask + (1 << from) + (1 << to)] = dp[mask] + dist[from][to];
                        prev[mask + (1 << from) + (1 << to)] = {from, to};
                    }
                }
                else if(to == n)
                {
                    if(dp[mask + (1 << from)] > dp[mask] + dist[from][to])
                    {
                        dp[mask + (1 << from)] = dp[mask] + dist[from][to];
                        prev[mask + (1 << from)] = {from, to};
                    }
                }
            }
            break;
        }
    }
    cout << always + dp.back() << endl;
    for(int mask = (1 << n) - 1; mask != 0;)
    {
        if(prev[mask].ss == n)
        {
            cout << 0 << ' ' << prev[mask].ff + 1 << ' ';
            mask -= (1 << prev[mask].ff);
        }
        else
        {
            cout << 0 << ' ' << prev[mask].ss + 1 << ' ' << prev[mask].ff + 1 << ' ';
            mask -= (1 << prev[mask].ff) + (1 << prev[mask].ss);
        } 
    }
    cout << 0 << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}