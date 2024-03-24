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
    ll n, m;
    cin >> n >> m;
    queue<pair<ll, int>> q;
    q.push(mp(n, 0));
    unordered_set<int> used;
    used.insert(n);
    while(true)
    {
        ll time = q.front().ss;
        ll val = q.front().ff;
        q.pop();
        if(val == m)
        {
            cout << time << endl;
            return;
        }
        if(!used.contains(val * 2) && m > val)
        {
            used.insert(val * 2);
            q.push(mp(val * 2, time + 1));
        }
        if(!used.contains(val - 1))
        {
            used.insert(val - 1);
            q.push(mp(val - 1, time + 1));
        }
    }
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