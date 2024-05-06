#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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
    ll n, k, ptrB, ptrS;
    cin >> n >> k >> ptrB >> ptrS;
    vector<ll> perm(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> perm[i];
    }
    vector<ll> a(n + 1);
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> a[i];
    }
    if(ptrB == ptrS)
    {
        cout << "Draw" << endl;
        return;
    }
    vector<pair<ll, ll>> dpS(n + 1, {numeric_limits<ll>::min(), numeric_limits<ll>::max()}), dpB(n + 1, {numeric_limits<ll>::min(), numeric_limits<ll>::max()});

    dpS[ptrS] = {0, 0};
    dpB[ptrB] = {0, 0};
    vector<bool> used(n + 1);
    auto go = [&a, &k, &perm, &used, &n](vector<pair<ll, ll>>& dp, ll ptr)
    {
        int from = -1;
        used[ptr] = true;
        from = ptr;
        ptr = perm[ptr];
        for(int i = 1; !used[ptr]; ++i)
        {
            if(used[ptr]) break;
            used[ptr] = true;
            dp[ptr] = {dp[from].ff + a[from], i};
            from = ptr;
            ptr = perm[ptr];
        }
    };
    go(dpS, ptrS);
    used.assign(n + 1, false);
    go(dpB, ptrB);
    ll scoreS = 0;
    for(ll i = 1; i < n + 1; ++i)
    {
        ll actions = dpS[i].ss;
        ll sum = dpS[i].ff;
        if(actions <= k) scoreS = max(scoreS, sum + (k - actions) * a[i]);
    }
    ll scoreB = 0;
    for(ll i = 1; i < n + 1; ++i)
    {
        ll actions = dpB[i].ss;
        ll sum = dpB[i].ff;
        if(actions <= k) scoreB = max(scoreB, sum + (k - actions) * a[i]);
    }
    if(scoreS == scoreB)
    {
        cout << "Draw\n";
    }
    else if(scoreB < scoreS)
    {
        cout << "Sasha\n";
    }
    else cout << "Bodya\n";
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}