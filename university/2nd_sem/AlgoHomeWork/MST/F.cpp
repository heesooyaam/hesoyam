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
//#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'

void solve()
{
    ll n;
    ll ans = 0;
    cin >> n;
    int lac = -2e9, lar = -2e9, mr = 0, mc = 0, lap = -2e9;

    for(int i = 1; i <= n; ++i)
    {
        int x = 0;
        char c;
        cin >> x >> c;
        if(c == 'G' || c == 'R')
        {
            if (lar != -2e9)
            {
                ans += x - lar;
                mr = max(mr, x - lar);
            }
            lar = x;
        }
        if(c == 'G' || c == 'B')
        {
            if (lac != -2e9)
            {
                ans += x - lac;
                mc = max(mc, x - lac);
            }
            lac = x;
        }
        if(c == 'G')
        {
            if(lap != -2e9)
            {
                ans += min(0ll, 0ll - mr - mc + x - lap);
            }
            lap = x;
            mc = mr = 0;
        }
//		cout<<ans<<" qwe?\n";
    }
    cout << ans << endl;
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

// 1G ... 5R ... 10B ... 15G