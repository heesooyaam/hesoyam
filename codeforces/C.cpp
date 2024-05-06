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
    vector<ll> x(n);
    ll mx = numeric_limits<ll>::min();
    for(int i = 1; i < n; ++i)
    {
        cin >> x[i];
        mx = max(mx, x[i]);
    }
    ll mod = mx + 1;
    vector<ll> a(n);
    a[0] = mod;
    for(int i = 1; i < n; ++i)
    {
        if(x[i] < a[i - 1])
        {
            a[i] = a[i - 1] + x[i];
        }
        else
        {
            a[i] = (x[i] / a[i - 1] + 1) * a[i - 1] + x[i];
        }
    }
    for(int i = 1; i < n; ++i)
    {
        assert(a[i] % a[i - 1] == x[i]);
    }
    print(a);

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