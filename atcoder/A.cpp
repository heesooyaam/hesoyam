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
vector<ll> money = {1, 5, 10, 50, 100, 500};

void solve() {
    vector<ll> cnt(6);input(cnt);
    int n;
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < 6; ++i) {
        sum += money[i] * cnt[i];
    }
    vector<ll> cost(n);input(cost);
    ll all_cost = 0;
    for (int i = 0; i < n; ++i)
    {
        all_cost += cost[i];
    }
    if(all_cost > sum)
    {
        cout << "No\n";
        return;
    }
    sort(all(cost), [](const ll& a, const ll& b) {return a > b;});
    bool ok = true;
    for(int i = 0; i < n && ok; ++i)
    {
        for(int j = 5; j >= 0; --j)
        {
            ll can_take = min(cost[i] / money[j], cnt[j]);

            cost[i] -= money[j] * can_take;
            cnt[j] -= can_take;
        }
        ok = (cost[i] == 0);
    }
    if(ok)
    {
        cout << "Yes\n";
    }
    else cout << "No\n";

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