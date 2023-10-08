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
    int n;
    cin  >> n;
    vector <int> c (n);
    for(int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    sort(all(c));
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i)
    {
        int money; cin >> money;
        cout << ((upper_bound(all(c), money)) - c.begin()) << endl;
    }   
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}