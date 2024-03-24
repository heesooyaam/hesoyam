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
ll MOD = 1'000'000'007;
vector<ll> power2;
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<ll> vec(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
    }
    ll cur = 0;
    ll mx = *max_element(all(vec));
    if(mx < 0)
    {
        // cout << "!" << endl;
        ll sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += vec[i] + MOD;
            sum %= MOD;
        }
        // cout << sum << endl;
        cout << (sum + MOD) % MOD << endl;
        return;
    }
    else if(mx == 0)
    {
        ll sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += vec[i] + MOD;
            sum %= MOD;
        }
        cout << (sum + MOD) % MOD << endl; return;
    }
    for(int i = 0; i < n; ++i)
    {
        mx = max(cur, mx);
        if(cur + vec[i] > 0)
        {
            cur += vec[i];
        }
        else
        {
            cur = 0;
        }
        mx = max(cur, mx);
    }
    mx %= MOD;
    ll sum = 0;
    for(int i = 0; i < n; ++i)
    {
        sum += vec[i];
    }
    cout << (sum + (mx * ((power2[k]) - 1) % MOD) + MOD) % MOD << endl;
    
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    power2.assign(2e5 + 10, 1);
    for(int i = 1; i < power2.size(); ++i)
    {
        power2[i] = (power2[i - 1] * 2) % MOD;
    }
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}