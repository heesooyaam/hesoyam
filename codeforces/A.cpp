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
    int cnt1 = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
        cnt1 += vec[i] == 1;
    }
    if(cnt1 == 1) 
    {
        cout << 0 << endl;
        return;
    }
    int start = find(all(vec), 1) - vec.begin();
    int end = n - 1;
    for(; end >= 0; --end)
    {
        if(vec[end] == 1) break;
    }
    ll ans = 0;
    for(int i = start; i < end; ++i)
    {
        if(vec[i] == 0)
        {
            ++ans;
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