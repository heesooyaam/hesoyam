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
    ll n;
    cin >> n;
    ll quad = n * n;
    ll ans = 0;
    for(ll x = 0; x <= n; ++x)
    {
       ll min_y = quad - x * x;
       ll y = sqrtl(min_y);
       ll cur = 0;
       while((y * y + x * x) < (n + 1) * (n + 1))
       {
           if(y * y + x * x >= quad)
           {
               if(x * y == 0 && x + y != 0) ans += 2;
               else if(x * y == 0 && x + y == 0) ans += 1;
               else if(x * y != 0 && x + y != 0) ans += 4;
           }
            ++y;
       }
    }
    cout << ans << endl;
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