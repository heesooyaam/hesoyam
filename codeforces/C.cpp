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
int n;   
int go(vector<int>& vec, int div)
{
    int k = n / div;
    int nod = 0;
    for(int q = 0; q < div && nod != 1; ++q)
    {
        for(int m = 1; m < k && nod != 1; ++m)
        {
            nod = gcd(nod, abs(vec[div * m + q] - vec[div * (m - 1) + q]));
        }
    }
    return int(nod != 1);
}
void solve()
{
    cin >> n;
    vector<int> vec(n);
    input(vec);
    ll ans = 0;
    // cout << n << "'divisors: ";
    for(int div = 1; div * div <= n; ++div)
    {
        if(n % div) continue;
        // cout << div << ", "; 
        ans += go(vec, div);
        if(div * div == n) continue;
        // cout << n / div << ", ";
        ans += go(vec, n / div);
    }
    // cout << endl << "points = ";
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