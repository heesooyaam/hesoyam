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
    vector<ll> vec(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
    }
    ll x = vec[1] - vec[0];
    ll ans = numeric_limits<ll>::max();
    for(ll a1 : {vec[0] - 1, vec[0], vec[0] + 1})
    {
        for(ll a2 : {vec[1] - 1, vec[1], vec[1] + 1})
        {
            ll d = a2 - a1;
            ll cnt = a1 != vec[0] + a2 != vec[1];
            ll prev = a2;
            bool ok = false;
            for(int i = 2; i < n; ++i)
            {
                for(int delta : {-1, 0, 1})
                {
                    if(prev + d == vec[i] + delta)
                    {
                        ok = true;
                        prev = vec[i] + delta;
                        cnt += delta != 0;
                        break;
                    }
                }
            }
        }
    }
    if(ans == numeric_limits<ll>::max())
    {
        cout << -1 << endl;
    }
    else cout << ans << endl;

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