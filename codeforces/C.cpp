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
    int n;
    cin >> n;
    vector<int> vec(n);
    input(vec);
    vector<int> a, b;
    a.pb(vec[0]);
    b.pb(1e9 + 10);
    for(int i = 1; i < n - 1; ++i)
    {
        if(vec[i] <= a.back() && vec[i] <= b.back())
        {
            
                if(vec[i] - a.back() > vec[i] - b.back())
                {
                    a.pb(vec[i]);
                }
                else b.pb(vec[i]);
            
        }
        else if(vec[i] <= a.back())
        {
            a.pb(vec[i]);
        }
        else if(vec[i] <= b.back())
        {
            b.pb(vec[i]); 
        }
        else
        {
            if(vec[i] - a.back() > vec[i] - b.back())
            {
                a.pb(vec[i]);
            }
            else b.pb(vec[i]);
        }
    }
    if(vec.back() <= a.back())
    {
        a.pb(vec.back());
    }
    else b.push_back(vec.back());
    ll ans = 0;
    for(int i = 0; i < a.size() - 1; ++i)
    {
        if(a[i] < a[i + 1]) ++ans;
    }
    for(int i = 0; i < b.size() - 1; ++i)
    {
        if(b[i] < b[i + 1]) ++ans;
    }
    // cout << "a: "; print(a);
    // cout << "b: "; print(b);
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