//
// Created by topcr on 04.04.2024.
//
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
    ull n, k;
    cin >> n >> k;
    vector<ull> messages(n);
    input(messages);
    auto ok = [&](ull mid)
    {
        bool okay = true;
        ull prev = 1;
        for(int i = 1; i < n && okay; ++i)
        {
            if(messages[i] + k < prev * mid) okay = false;
            prev *= mid;
        }
        return okay;
    };
    ull l = 1, r = pow(ld(messages.back() + k), ld(1) / ld(n - 1)) + 2;
    while(l + 1 < r)
    {
        ull mid = (l + r) >> 1;
        if(ok(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if(ok(r)) cout << r << endl;
    else cout << l << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}