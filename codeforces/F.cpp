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
    int idx, pos;
    bool begin;
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<event> events;
    vector<pair<int, int>> borders(m);
    for(int i = 0; i < m; ++i)
    {
        int l, r;
        cin >> l >> r;
        events.pb({i, l, true});
        events.pb({i, r + 1, false});
        borders[i].ff = l;
        borders[i].ss = r;
    }
    auto events_cmp = [](event& A,event& B)->bool
    {
        return A.pos < B.pos;
    };
    sort(all(events), events_cmp);
    multiset<int> st;
    vector<ll> dp(n + 2, 0);
    auto ptr = 0;
    for(int round = 1; round <= n; ++round)
    {
        while(ptr < events.size() && events[ptr].pos <= round)
        {
            if(events[ptr].begin)
            {
                st.insert(events[ptr].pos);
            }
            else
            {
                st.erase(st.find(borders[events[ptr].idx].ff));
            }
            ++ptr;
        }
        if(st.size() == 0)
        {
            dp[round] = dp[round - 1];
            continue;
        }
        int prev = *st.begin() - 1;
        dp[round] = max(dp[round - 1], dp[prev] + (ll) st.size());
        // cout << prev << endl;
    }
    // cout << "!!!" << endl;
    cout << dp[n] << endl;

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