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

void solve()
{
    ll n, idx;
    cin >> n >> idx;

    auto ok = [&](const ll& mid)->bool
    {
        return ((mid * (mid + 1) / 2) >= idx);
    };

    ll l, r;
    l = 1; r = n - 1;
    while(l + 1 < r)
    {
        ll mid = (l + r) / 2;
        if(ok(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }

    ll firstB;
    if(ok(l)) firstB = l;
    else firstB = r;

    ll secondB = (firstB - 1) - (firstB * (firstB + 1) / 2 - idx);

    string ans;
    for(int i = 0; i < n; ++i)
    {
        if(i == firstB || i == secondB)
        {
            ans += 'b';
        }
        else ans += 'a';
    } 

    reverse(all(ans));

    cout << ans << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}