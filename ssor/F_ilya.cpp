#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
using ll = long long;

ll k;

bool isOk(ll curSum, vector<ll>& a){
    ll cnt = 0;
    for (int i = 0; i < a.size(); ++i) {
        int mxIdx = upper_bound(a.begin(), a.end(), curSum - a[i]) - a.begin();
        mxIdx = min(mxIdx, i);
        int add = mxIdx;
        cnt += add;
    }
    return cnt >= k;
}

void solve() {
    int n;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto &v: a) {
        cin >> v;
    }
    sort(a.begin(), a.end());
    ll l = 0;
    ll r = 1e18;
    while (l < r - 1) {
        ll m = (l + r) / 2;
        if (isOk(m, a)) {
            r = m;
        } else {
            l = m;
        }
    }
    if (isOk(l, a)) {
        r = l;
    }
    cout << r << endl;
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

