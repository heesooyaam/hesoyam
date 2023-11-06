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
    vector<vector<int>> dp(n, vector<int> (m, 0));
    vector<int> prev(n, -1);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            dp[i][j] = int(a[i] == b[j]);
        }
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 1; j < m; ++j)
        {
            if(a[i] == b[j])
            {
                for(int ii = 0; ii < i; ++ii)
                {
                    if(a[ii] < a[i] && dp[ii][j] + 1 > dp[i][j])
                    {
                        dp[i][j] = dp[ii][j] + 1;
                        prev[i] = ii;
                    }
                }
            }
            else dp[i][j] = dp[i][j - 1];
        }
    }
    int ans = 0;
    int idxOfLast = 0;
    for(int i = 0; i < n; ++i)
    {
        if(dp[i][m - 1] > ans)
        {
            ans = dp[i][m - 1];
            idxOfLast = i;
        }
    }
    
    cout << ans << endl;
    if(ans == 0)
    {
        return;
    }
    vector <int> answer;
    int cur = idxOfLast;
    do
    {
        answer.pb(a[cur]);
        cur = prev[cur];
    } while(cur != -1);
    reverse(all(answer));
    print(answer);
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}