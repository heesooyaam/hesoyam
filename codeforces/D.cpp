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
#define int long long 

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<int> vec(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> vec[i];
    }
    vector<int> bits(31);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= 30; ++j)
        {
            bits[j] += (vec[i] >> j) & 1;
        }
    }
    ll ans = -1;
    int start = 30;
    for(; start >= 0; --start)
    {
        if((x >> start) & 1) break;
    }
    cout << start << endl;
    for(int i = 30; i >= 0; --i)
    {
        int bit = (x >> i) & 1;
        if(bits[i] % 2 == 0)
        {
            if(bit) continue;
            ans = (bits[i] == 0) ? n : bits[i] / 2;
            break;
        }
        else
        {
            if(bit) break;
        }
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