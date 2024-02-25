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
    int n, q;
    cin >> n >> q;
    vector<ll> vec(n + 1);
    for(int i = 1; i < n + 1; ++i) cin >> vec[i];
    vector<ll> cnt1(n + 1), cnt(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cnt1[i] = cnt1[i - 1] + (vec[i] == 1);
        cnt[i] = cnt[i - 1] + (vec[i] - 1);
    }
    for(int i = 0; i < q; ++i)
    {
        int l, r;
        cin >> l >> r;
        if(l == r)
        {
            cout << "NO\n";
            continue;
        }

        if(cnt1[r] - cnt1[l - 1] > cnt[r] - cnt[l - 1]) cout << "NO\n";
        else cout << "YES\n";   
    }
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