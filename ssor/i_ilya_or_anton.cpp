#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll = long long;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v: a) {
        cin >> v;
    }
    a.insert(a.begin(), 0);
    int x, y;
    cin >> x >> y;
    multiset<ll> got;
    ll sum = 0;
    vector<ll> dp(n + 1, -1);
    dp[0] = 0;
    for (int i = x; i <= n; ++i) {
        got.insert(dp[i - x]);
        if (i - y >= 0) {
            auto it = got.find(dp[i - y]);
            if (it != got.end()) {
                got.erase(it);
            }
        }
        dp[i] = a[i] + *prev(got.end());
    }
    cout << dp[n] << endl;
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

