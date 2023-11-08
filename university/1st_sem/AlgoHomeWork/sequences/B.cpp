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
    int n; cin >> n;
    vector <int> vec (n);
    for(int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    vector<int> d(n + 1, INT_MAX);
    d[0] = 0;
    int mxLen = 0;
    for(int i = 0; i < n; ++i)
    {
        int len = upper_bound(all(d), vec[i]) - d.begin();
        d[len] = vec[i];
        mxLen = max(mxLen, len);
    }
    cout << mxLen << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}