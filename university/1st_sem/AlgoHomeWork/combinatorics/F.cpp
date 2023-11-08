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
void three(vector<ll>& flowers)
{
    int cnt = *min_element(all(flowers)) / 3;
    for(int i = 0; i < 3; ++i)
    {
        flowers[i] -= cnt * 3;
    }
    flowers[3] += cnt * 3;
}
void last(vector<ll>& flowers)
{
    for(int i = 0; i < 3; ++i)
    {
        flowers[3] += flowers[i] / 3;
    }
}
void solve()
{
    ll r, g, b;
    cin >> r >> g >> b;
    vector<ll> case1(4), case2(4), case3(4);
    for(int i = 0; i < 3; ++i)
    {
        case1[i] = case2[i] = case3[i] = (i == 0) ? r : ((i == 1) ? g : b);
    }
    int x = 0;
    if(min({r, g, b}) >= x)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(i == 3) case1[i] += x;
            else case1[i] -= x;
        }
    }  
    if(min({r, g, b}) >= ++x)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(i == 3) case2[i] += x;
            else case2[i] -= x;
        }
    }  
    if(min({r, g, b}) >= ++x)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(i == 3) case3[i] += x;
            else case3[i] -= x;
        }
    }  
    for(auto* flowers : {&case1, &case2, &case3})
    {
        three(*flowers);
        last(*flowers);
    }
    
    cout << max({case1[3], case2[3], case3[3]}) << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}