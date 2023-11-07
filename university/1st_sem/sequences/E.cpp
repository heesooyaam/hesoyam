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
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;
    vector<vector<int>> LCS(n, vector<int> (m, 0));
    if(a[0] == b[0]) LCS[0][0] = 2;
    for(int i = 1; i < m; ++i)
    {
        if(a[0] == b[i]) LCS[0][i] = 2;
    }
    for(int i = 1; i < n; ++i)
    {
        if(a[i] == b[0]) LCS[i][0] = 2;
    }
    for(int i = 1; i < n; ++i)
    {
        for(int j = 1; j < m; ++j)
        {
            if(a[i] == b[j])
            {
                LCS[i][j] = LCS[i - 1][j - 1] + 2;
            }
            else{
                LCS[i][j] = max({LCS[i - 1][j] - 1, LCS[i][j - 1] - 1, 0});
            }
        }
    }
    int mx = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            mx = max(LCS[i][j], mx);
        }
    }
    cout << mx << endl;
    cout << "  ";
    for(int i = 0; i < m; ++i)
    {
        cout << ' ' << b[i];
    }
    cout << endl << endl;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(j == 0) cout << a[i] << "  ";
            cout << LCS[i][j] << ' ';
        }
        cout << endl;
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    while(t--) solve();
    return 0;
}