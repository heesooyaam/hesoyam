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
    vector<int> cnt(n + 1, 0);
    for(int i = 0; i < n; ++i)
    {
        cnt[vec[i]] += 1;
    }
    vector<int> num(n + 2);
    for(int k = n; k >= 1; --k)
    {
        num[k] = cnt[k] + cnt[k + 1];
    }
    sort(num.begin() + 1, num.end() - 1);
    ll ans = 1;
    int cur = num[1];
    for(int i = 1; i < n + 2; ++i)
    {
        int cnt = upper_bound(num.begin() + 1, num.end() - 1, prev) - (num.begin() + i);
        ans *= 1ll * prev
        i = upper_bound(num.begin() + 1, num.end() - 1, prev) - (num.begin() + 1);
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}