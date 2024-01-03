#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'
using ll = long long;

const ll p = 37;
const ll MOD = 1e9 + 21;

vector<ll> MyPow(p);

ll Myhash(string& s, ll l, ll a) {
    ll hash1 = 0;
    for (ll i = a; i < a + l; ++i) {
        hash1 += (s[i] - 'a' + 1) * MyPow[i - a];
        hash1 %= MOD;
    }
    return hash1;
}

void solve()
{
    string s;
    cin >> s;
    ll q;
    cin >> q;
    for (ll i = 0; i < q; ++i) {
        ll l, a, b;
        cin >> l >> a >> b;
        ll hash1 = Myhash(s, l, a);
        ll hash2 = Myhash(s, l, b);
        // cout << hash1 << " " << hash2 << endl;
        // if (hash1 == hash2) {
        //     cout << "yes" << endl;
        // }
        // else {
        //     cout << "no" << endl;
        // }
        cout << 1 + i << endl;
    }
}

int main()
{
    // freopen("file.in", "r", stdin);
    // freopen("file.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);

    MyPow[0] = 1;
    for (int i = 1; i < p; ++i) {
        MyPow[i] = MyPow[i - 1] * p;
        MyPow[i] %= MOD;
    }

    int t = 1;
    // cin >> t;

    while(t--)
    {
        solve();
    }

    return 0;
}
