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

void solve()
{
    ll n, k;
    cin >> n >> k;
    vector <int> vec (n);
    for(int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    sort(all(vec));
    vector<int> val(n);
    for(int i = 0; i < n; ++i)
    {
        val[i] = vec[i];
    }
    val.resize(unique(all(val)) - val.begin());
    auto amount = [&](int idx)->int // returns amount of numbs in vec which are lower than val[idx]
    {
        return lower_bound(all(vec), val[idx]) - vec.begin();
    };
    vector<ll> prefCNT(val.size());
    for(int i = 1; i < val.size(); ++i)
    {
        prefCNT[i] = prefCNT[i - 1] + amount(i);
    }
    vector<ll>suffCNT(n);
    for(int i = n - 2; i >= 0; --i)
    {
        suffCNT[i] = suffCNT[i + 1] + vec.size() - amount(i + 1);
    }
    ll l, r;
    l = 0; r = *max_element(next(vec.begin()), vec.end()) - *min_element(next(vec.begin()), vec.end());
    auto ok = [&](ll& dif)->bool
    {
        for(int i = 0; i <= n - dif - 1; ++i)
        {
            if(prefCNT[i] + suffCNT[i + dif] <= k) return true;
        }
        return false;
    };
    while(l + 1 < r)
    {
        ll mid = (l + r) / 2;
        if(ok(mid))
        {
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}