#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll = long long;

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto& [x, y] : v)
    {
        cin >> x >> y;
    }

    ll ans = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (v[i].first != v[j].first and v[i].second != v[j].second)
            {
                int curx = abs(v[i].first -v[j].first);
                int cury = abs(v[i].second -v[j].second);

                if ((4 * curx == 3 * cury) || (3 * curx == 4 * cury))
                {
                    ans++;
                }
            }
        }
    }
    cout << ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    // cin >> t;

    while(t--)
    {
        solve();
    }

    return 0;
}
