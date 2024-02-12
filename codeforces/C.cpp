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
    ll pos, x;
    cin >> pos >> x;
    --pos;
    set<ll> st;
    ll fwd = pos + (x - 1);
    ll back = pos - (x - 1);
    cout << "divisors of " << fwd << ": ";
    for(ll i = 1; i * i <= fwd; ++i)
    {
        if(fwd % i) continue;
        cout << fwd / i << ", " << i << ", ";
        ll k1 = -1, k2 = -1;
        
        if(i % 2 == 0) k1 = i / 2 + 1;
        if((fwd / i) % 2 == 0) k2 = fwd / i / 2 + 1;

        for(auto& k : {k1, k2})
        {
            if(k != -1 && k != 1) st.insert(k);
        }
    }
    cout << endl;
    cout << "divisors of " << back << ": ";
    for(ll i = 1; i * i <= back; ++i)
    {
        if(back % i) continue;
        cout << back / i << ", " << i << ", ";
        ll k1 = -1, k2 = -1;
        
        if(i % 2 == 0) k1 = i / 2 + 1;
        if((back / i) % 2 == 0) k2 = back / i / 2 + 1;

        for(auto& k : {k1, k2})
        {
            if(k != -1 && k != 1) st.insert(k);
        }
    }
    cout << endl;
    cout << "k's: "; print(st);
    cout << st.size() << endl;
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