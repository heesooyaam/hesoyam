#include <bits/stdc++.h>
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
ll countDays(const ll& d, const ll& x)
{
    return d / (x + 1) + bool(d % (x + 1)) + x;
}
void solve()
{
    ll n, d;
    cin >> n >> d;
    if((n + 1) * (n + 1) == 4 * d)
    {
        cout << "YES\n";
        return;
    }
    // days = x + [d / (x + 1)]
    ll l = 0, r = n;
    int T = 100;
    while(T--)
    {
        ll mid1 = (2 * l + r) / 3;
        ll mid2 = (l + 2 * r) / 3;
        ll ans1 = countDays(d, mid1);
        ll ans2 = countDays(d, mid2);

        if(min(ans1, ans2) <= n)
        {
            cout << "YES\n";
            return;
        }

        if(ans1 < ans2)
        {
            r = mid2 - 1;
        }
        else{
            l = mid1 + 1;
        }

    }
    //cout << l << ' ' << r << endl;
    for(int i = l; i <= r; ++i)
    {
        if(countDays(d, i) <= n)
        {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";

}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}