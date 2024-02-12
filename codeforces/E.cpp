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
    int n, k;
    cin >> n >> k;
    vector<int> p(n + 1);
    int mx = n;
    int mn = 1;

    for(int i = 1; i <= k; ++i)
    {
        for(int q = 0; q * k + i <= n; ++q)
        {
            int pos = q * k + i;
            if(i & 1)
            {
                p[pos] = mx--;
            }
            else
            {
                p[pos] = mn++;
            }
        }
    }
    for(int i = 1; i < n + 1; ++i)
    {
        cout << p[i] << ' ';
    }
    cout << endl;
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