#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll = long long;

void solve()
{
    string s;
    cin >> s;
    s += '.';
    vector<int> sz;
    int cur = 0;
    for (auto c: s) {
        if (c == '.') {
            if (cur) {
                sz.push_back(cur);
                cur = 0;
            }
        } else {
            cur++;
        }
    }
    sort(sz.rbegin(), sz.rend());
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v: a) {
        cin >> v;
    }
    sort(a.begin(), a.end());
    ll ans = 0;
    for (int i = 0; i < sz.size(); ++i) {
        ans += 1ll * sz[i] * a[i];
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
