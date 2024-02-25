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

template<typename T>
ll binpow(T val, unsigned int n, const ll MOD = 1e9 + 7)
{
    ll ans = 1;
    ll cur = val;
    while(n)
    {
        if(n & 1)
        {
            ans *= cur;
            ans %= MOD;
        }
        cur *= cur;
        cur %= MOD;
        n >>= 1;
    }
    return ans;
}
template<typename T>
ll recBinPow(T val, unsigned int n, const ll MOD = 1e9 + 7)
{
    if(n == 0) return 1;

    ll t = recBinPow(val, n >> 1, MOD);

    if(n & 1) return (((t * val) % MOD) * t) % MOD;
    else return (t * t) % MOD;
}

void solve()
{
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