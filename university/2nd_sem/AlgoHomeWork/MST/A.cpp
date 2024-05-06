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
#define make_unique(x) sort(all(x)); (x).resize(unique(all(x)) - x.begin())
#define endl '\n'

void solve()
{
    ll n, m;
    ll p1, p2;
    cin >> n >> m >> p1 >> p2;
    auto count = [&](ll x1, ll y1, ll x2, ll y2)
    {
        return (x1 * x2 + p1 * y1 * y2) % p2;
    };
    set<pair<ll, pair<ll, ll>>> q;
    q.insert({0, {1, 1}});
    vector<vector<bool>> used(n + 1, vector<bool> (m + 1, false));
    vector<vector<ll>> minEdge(n + 1, vector<ll> (m + 1, numeric_limits<ll>::max()));
    vector<pair<ll, ll>> moves =  {{0, 1}, {1, 0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}};
    ll counter = n * m;
    ll ans = 0;
    while(counter)
    {
        auto cur = *q.begin();
        ll curR = cur.ss.ff, curC = cur.ss.ss;
        q.erase(q.begin());

        if(used[curR][curC]) continue;

        used[curR][curC] = true;
        --counter;
        ans += cur.first;
        for(const auto& [dR, dC] : moves)
        {
            ll nxtR = curR + dR;
            ll nxtC = curC + dC;

            if(nxtR < 1 || nxtR > n || nxtC < 1 || nxtC > m || used[nxtR][nxtC]) continue;

            ll cost = count(curR, curC, nxtR, nxtC);
            if(minEdge[nxtR][nxtC] > cost)
            {
                if(minEdge[nxtR][nxtC] != numeric_limits<ll>::max()) q.erase({minEdge[nxtR][nxtC], {nxtR, nxtC}});

                q.insert({count(curR, curC, nxtR, nxtC), {nxtR, nxtC}});
            }
        }
    }

    cout << ans << endl;

}
int32_t main()
{
    // freopen("bees.in", "r", stdin);
    // freopen("bees.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}