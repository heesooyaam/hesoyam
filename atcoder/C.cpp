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
    ull x;
    cin >> x;
    ull num = x;
    ll ans = 0;
    map<ull, ll> cnt;
    cnt[x] = 1;
    while(cnt[1] != num)
    {
        ull val = prev(cnt.end())->ff;
        ll amt = prev(cnt.end())->ss;
        if(val == 1) break;
        if(val & 1)
        {
            cnt[val / 2] += amt;
            cnt[val / 2 + 1] += amt;
            ans += val * amt;
        }
        else
        {
            cnt[val / 2] += amt * 2;
            ans += amt * val;
        }
        cnt.erase(prev(cnt.end()));
    }

    cout << ans << endl;
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