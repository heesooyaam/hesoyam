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
struct border
{
    ll l, r;
    ll time;
};
void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<border> borders(k);
    borders[0].l = 0;
    vector<ll> rights(k);
    for(int i = 0; i < k; ++i)
    {
        ll r;
        cin >> r;
        borders[i].r = r;
        rights[i] = r;
        if(i + 1 < k) borders[i + 1].l = r;
    }
    for(int i = 0; i < k; ++i)
    {
        ll t;
        cin >> t;
        borders[i].time = t;
    }
    auto v = [&](int idx)
    {
        return (ld) (borders[idx].r - borders[idx].l) / borders[idx].time;
    };
    for(int i = 0; i < q; ++i)
    {
        ll x;
        cin >> x;
        if(x == 0)
        {
            cout << 0 << endl;
            continue;
        }
        int last_idx = lower_bound(all(rights), x) - rights.begin();
        if(last_idx == 0)
        {
            cout << (ll) (x * borders[last_idx].time / ((borders[last_idx].r - borders[last_idx].l))) << ' ';
        }
        else
        {
            ll last_x = x - borders[last_idx].l;
            ll last_time = borders[last_idx].time - borders[last_idx - 1].time;
            cout << borders[last_idx - 1].time + last_x * last_time / (borders[last_idx].r - borders[last_idx].l) << ' ';
        }
    }
    cout << endl;
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