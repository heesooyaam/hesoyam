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
    int n, m;
    cin >> n >> m;
    vector <int> vec (n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> vec[i];
    }
    vector <int> pref(n + 1);
    for(int i = 1; i < n + 1; i++)
    {
        pref[i] = pref[i - 1] + vec[i];
    }
    vector<vector<int>> dp (n + 1, vector <int> (k + 1));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= k; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i - m][j - 1]);
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