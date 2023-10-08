#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ss second
#define ff first
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> victories(n);
    deque<pair<int, int>> q;
    for(int i = 0; i < n; ++i)
    {
        int x; cin >> x;
        q.eb(x, i);
    }
    vector <vector<int>> events (m, vector<int> (3));
    for(int i = 0; i < m; ++i)
    {
        cin >> events[i][1] >> events[i][0];
        events[i][2] = i;
    }
    vector <int> ans(m);
    sort(all(events));
    int rounds = 0;
    int ptr = 0;
    do
    {
        for(; ptr < ans.size() && events[ptr][0] == rounds; ++ptr)
        {
            ans[events[ptr][2]] = victories[events[ptr][1]];
        }

        auto first = q.front();
        q.ppf();
        if(first.ff > q.front().ff)
        {
            auto second = q.front();
            q.ppf();
            q.pb(second);
            q.pf(first);
            ++victories[first.ss];
        }
        else
        {
            ++victories[q.front().ss];
            q.pb(first);
        }
        ++rounds;
    }while(q.front().ff != n);
    
    for(; ptr < m; ++ptr)
    {
        if(events[ptr][1] == n)
        {
            ans[events[ptr][2]] = victories[events[ptr][1]] + events[ptr][0] - rounds;
        }
        else ans[events[ptr][2]] = victories[events[ptr][1]];
    }

    for(int i = 0; i < m; ++i)
    {
        cout << ans[i] << endl;
    }
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}