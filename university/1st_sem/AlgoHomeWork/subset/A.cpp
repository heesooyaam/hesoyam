#include <bits/stdc++.h>
#include <bit>
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
//#define endl '\n'  
int n; 
int getMaxBit(const int& x)
{
    for(int i = n - 1; true; --i)
    {
        if((1 << i) & x) return i;
    }
}
int getMinBit(const int& n)
{
    for(int i = 0; true; ++i)
    {
        if((1 << i) & n) return i;
    }
}
void solve()
{
    int l, r, d;
    cin >> n >> l >> r >> d;
    vector<int> c(n);
    input(c);
    sort(all(c));
    int ans = 0;
    int MAX = 1 << n;
    vector<int> dp((1 << n));
    for(int set = 0; set < MAX; ++set)
    {
        for(int i = 0; (1 << i) <= set; ++i)
        {
            if(set & (1 << i))
            {
                int subset = set - (1 << i);
                dp[set] = dp[subset] + c[i];
                // cout << bitset<10>(set) << ' ' << c[getMaxBit(set)] << ' ' << c[getMinBit(set)] << endl;
                if(subset && (dp[set] <= r) && (dp[set] >= l) && ((c[getMaxBit(set)] - c[getMinBit(set)]) >= d)) ++ans;
                break; 
            }
        }
    }
    // for(int i = 0; i < (1 << n); ++i)
    // {
    //     int sum = 0;
    //     for(int j = 0; (1 << j) < (1 << n); ++j)
    //     {
    //         if((1 << j) & i) sum += c[j];
    //     }
    //     cout << bitset<10>(i) << endl;
    //     assert(sum == dp[i]);
    // }
    // int x = 905;
    // cout << getMaxBit(x) << ' ' << getMinBit(x) << endl;
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}