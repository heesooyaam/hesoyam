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
    int n, m;
    string s, q;
    cin >> n >> m >> s >> q;
    ll ans = 0;
    for(int ptrS = 0, ptrQ = 0; ptrS < n; ++ptrS, ans = ptrS)
    {
        while(ptrQ < m && q[ptrQ] != s[ptrS]) ++ptrQ;

        if(ptrQ == m)
        {
            ans = ptrS;
            break;
        }
        else ++ptrQ;
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