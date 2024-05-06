#include <bits/stdc++.h>
#include <bit>
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
    auto log2 = [](unsigned n)->int
    {
        return sizeof(n) * 8 - __countl_zero(n) - 1;
    };
    unsigned n;
    cin >> n;
    vector<ll> vec(n);
    input(vec);
    int power = log2(n);
    vector<vector<ll>> sparceTable(power, vector<ll> (n, 0));
    // sparceTable[i][j] = bitOR on segment, which starts in j and has length = 2^i
    for(int i = 0; i < n; ++i)
    {
        sparceTable[0][i] = vec[i];
    }
    for(int i = 1; i < power; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            sparceTable[i][j] = sparceTable[i - 1][j] |
            (((j + (1 << (i - 1))) < n) ? sparceTable[i - 1][j + (1 << (i - 1))] : 0);
        }
    }

    auto ask = [sparceTable, log2](int l, int r)->ll
    {
        unsigned len = r - l + 1;
        return sparceTable[log2(len)][l] | sparceTable[log2(len)][r - (1 << log2(len)) +    1];
    };
    int req;
    cin >> req;
    while(req--)
    {
        int l, r;
        cin >> l >> r;
        cout << ask(l, r) << endl;
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}