#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    ll ans = v[n - 1] - v[0];
    ll l = 0;
    ll r = n - 1;
    ll cur = 0;
    while (l < r && k > 0) {
        if (l < n - r) {
            l++;
            cur = min(v[l] - v[l - 1], k / l);
            k -= cur * l;
        }
        else {
            cur = min(v[r] - v[r - 1], k / (n - r));
            k -= cur * (n - r);
            r--;
        }
        ans -= cur;
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}