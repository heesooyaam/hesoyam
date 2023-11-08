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
    int n;
    cin >> n;
    vector <int> a (n);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int m; cin >> m;
    vector <int> b (m);
    for(int i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    vector<vector<int>> dp(n, vector<int> (m));
    vector<int> prev(m, -1);
    for(int j = 0; j < m; ++j)
    {
        dp[0][j] = a[0] == b[j];
    }
    for(int i = 1; i < n; ++i)
    {
        int best = 0;
        int idxOfBest = -1;
        for(int j = 0; j < m; ++j)
        {
            dp[i][j] = dp[i - 1][j];

            if(b[j] < a[i] && dp[i][j] > best)
            {
                best = dp[i][j];
                idxOfBest = j;
            }
            else if(a[i] == b[j] && dp[i][j] < best + 1)
            {
                dp[i][j] = best + 1;
                prev[j] = idxOfBest;
            }
        }
    }

    vector<int> ans;
    int length = 0;
    int idx = 0;
    for(int j = 0; j < m; ++j)
    {
        if(dp[n - 1][j] > length)
        {
            length = dp[n - 1][j];
            idx = j;
        }
    }

    cout << length << endl;
    if(length == 0) return;

    do
    {
        ans.pb(b[idx]);
        idx = prev[idx];
    } while (idx != -1);
    reverse(all(ans));
    print(ans);
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}