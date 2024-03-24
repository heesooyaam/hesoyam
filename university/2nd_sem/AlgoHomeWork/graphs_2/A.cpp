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
    vector<vector<pair<int, char>>> g(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        char ch;
        cin >> ch;
        if(ch == '=')
        {
            g[i + 1].eb(i + 2, '=');
            g[i + 2].eb(i + 1, '=');
        }
        else if(ch == 'L')
        {
            g[i + 2].eb(i + 1, '<');
        }
        else
        {
            g[i + 1].eb(i + 2, '<');
        }
    }
    ll mx = 1;
    cout << -1 << endl;
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