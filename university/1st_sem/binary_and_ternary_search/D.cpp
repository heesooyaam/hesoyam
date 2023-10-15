#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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

inline bool ok(vector<int>& t,vector<int>& x, long double& time)
{
    long double mxL = -2e10, mnR = 2e10;
    for(int i = 0; i < n; ++i)
    {
        //if(time < t[i]) return false;
        mxL = max(mxL, 1.0 * x[i] - (time - t[i]));
        mnR = min(mnR, 1.0 * x[i] + (time - t[i]));
    }
    // cout << mxL << ' ' << mnR << endl;
    return mxL <= mnR;
}

void solve()
{
    cin >> n;
    vector <int> x (n);
    input(x);
    vector <int> t (n);
    input(t);

    long double l, r;
    l = *max_element(all(t)), r = [&](){ll mx=-2e10;ll L=*min_element(all(x)),R=*max_element(all(x));for(int i=0;i<n;++i)mx=max(mx,max(R-x[i],x[i]-L)+t[i]);return mx;}();

    int T = 34;
    while(T--)
    {
        long double mid = (l + r) / 2;
        if(ok(t, x, mid))
        {
            r = mid;
        }
        else{
            l = mid;
        }
    }
    
    long double ans = -2e10;
    for(int i = 0; i < n; ++i)
    {
        ans = max(ans, 1.0 * x[i] - ((r + l) / 2 - 1.0 * t[i]));
    }

    cout << fixed << setprecision(7) << ans << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}