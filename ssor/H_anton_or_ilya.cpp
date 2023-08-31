#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll = long long;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll ans = 0;
    for (auto& l: g) {
        ans += 1ll * l.size() * (l.size() - 1) / 2;
    }
    cout << ans << endl;
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
