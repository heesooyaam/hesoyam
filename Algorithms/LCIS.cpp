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
    // O(n^2 * m)
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
    cout << endl;

    vector<vector<int>> dp1(n, vector<int> (m, 0));
    vector<int> prev1(n, -1);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            dp1[i][j] = int(a[i] == b[j]);
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
                    if(a[ii] < a[i] && dp1[ii][j] + 1 > dp1[i][j])
                    {
                        dp1[i][j] = dp1[ii][j] + 1;
                        prev1[i] = ii;
                    }
                }
            }
            else dp1[i][j] = dp1[i][j - 1];
        }
    }
    int ans = 0;
    int idxOfLast = 0;
    for(int i = 0; i < n; ++i)
    {
        if(dp1[i][m - 1] > ans)
        {
            ans = dp1[i][m - 1];
            idxOfLast = i;
        }
    }
    cout << "O(n^2 * m): " <<  ans << endl;
    if(ans == 0)
    {
        return;
    }
    vector <int> answer;
    int cur = idxOfLast;
    do
    {
        answer.pb(a[cur]);
        cur = prev1[cur];
    } while(cur != -1);
    reverse(all(answer));
    print(answer);
    cout << endl;


    // O(n * m)

    vector<vector<int>> dp2(n, vector<int> (m, 0));
    vector<int> prev2(n, -1);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            dp2[i][j] = int(a[i] == b[j]);
        }
    }

    for(int j = 1; j < m; ++j)
    {
        int best = 0;
        int idxOfBest = -1;
        for(int i = 0; i < n; ++i)
        {
            dp2[i][j] = dp2[i][j - 1]; // если не берем a[i], то лучший вариант уже посчитан
            if(a[i] == b[j] && best + 1 > dp2[i][j])
            {
                dp2[i][j] = best + 1;
                prev2[i] = idxOfBest;
            }
            if(a[i] < b[j] && dp2[i][j - 1] > best)
            {
                best = dp2[i][j - 1];
                idxOfBest = i;
            }
        }
    }

    int idx = 0;
    int mxL = 0;
    for(int i = 0; i < n; ++i)
    {
        if(dp2[i][m - 1] > mxL)
        {
            idx = i;
            mxL = dp2[i][m - 1];
        }
    }

    cout << "O(n * m): " << mxL << endl;

    if(mxL == 0)
    {
        return;
    }

    vector<int> ans2;
    int curr = idx;
    do
    {
        ans2.pb(a[curr]);
        curr = prev2[curr];
    } while (curr != -1);
    reverse(all(ans2));
    print(ans2);
    cout << endl;
    

    // O(n^2 * m^2)

    vector<vector<int>> dp3 (n, vector<int> (m));

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(a[i] == b[j])
            {
                dp3[i][j] = 1;
                for(int ii = 0; ii < i; ++ii)
                {
                    for(int jj = 0; jj < j; ++jj)
                    {
                        if(a[ii] == b[jj] && a[ii] < a[i])
                        {
                            dp3[i][j] = max(dp3[i][j], dp3[ii][jj] + 1);
                        }
                    }
                }
            }
        }
    }

    int llong = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            llong = max(llong, dp3[i][j]);
        }
    }

    cout << "O(n^2 * m^2): " << llong << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}