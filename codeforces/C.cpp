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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i < n + 1; ++i) cin >> a[i];
    for(int i = 1; i < n + 1; ++i) cin >> b[i];
    vector<ll> prefA(n + 1, 0), prefB(n + 1, INT_MIN);
    for(int i = 1; i <= n; ++i)
    {
        prefA[i] = prefA[i - 1] + a[i];
        prefB[i] = max(prefB[i - 1], b[i]);
    }
    ll mx = INT_MIN;
    for(int i = 1; i <= min(n, k); ++i)
    {
        mx = max(mx, prefA[i] + (k - i) * prefB[i]);
    }
    cout << mx << endl;
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