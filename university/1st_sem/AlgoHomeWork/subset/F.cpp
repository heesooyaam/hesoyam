#include <iostream>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
    // divisors: 2, 3, 5, 7,   6, 10, 14, 15, 21, 35,    30, 42, 70, 105,    210
    ll ans = n - (n / 2 + n / 3 + n / 5 + n / 7 - (n / 6 + n / 10 + n / 14 + n / 15 + n / 21 + n / 35 - ((n / 30 + n / 42 + n / 70 + n / 105) - n / 210)));
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}