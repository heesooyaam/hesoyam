#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   

void solve()
{
    int n; cin >> n;
    vector <int> vec (n);
    for(int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    vector <int> pref(n);
    for(int i = 0; i < n; ++i)
    {
        if(i > 0){
            pref[i] = pref[i - 1];
        }
        pref[i] += vec[i] >= 0;
    }
    vector <int> suff(n);
    for(int i = n - 1; i >= 0; --i)
    {
        if(i < n - 1)
        {
            suff[i] = suff[i + 1];
        }
        suff[i] += vec[i] <= 0;
    }
    int ans = n;
    for(int i = 0; i < n - 1; ++i)
    {
        ans = min(ans, pref[i] + suff[i + 1]);
    }
    cout << ans << endl;

}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(t--) solve();
    return 0;
}