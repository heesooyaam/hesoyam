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
// #define ss second
#define ff first
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'  

// struct custom_hash
// {
//     static uint64_t splitmix64(uint64_t x)
//     {
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }

//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };

struct request
{
    int s, d, k;
};

inline void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> vec(n + 1);
    for(int i = 1; i < n + 1; ++i) cin >> vec[i];
    // unordered_map<int, unordered_set<int, custom_hash>> mp;
    vector<request> r(q);
    unordered_map<int, unordered_map<int, vector<vector<ll>>>> pref;
    auto makePref = [&](int& d, int& start)->void
    {
        if(pref.contains(d) && pref[d].contains(start)) return;

        pref[d][start].assign(2, vector<ll>(n / d + 2, 0));
        ll m = 1;
        for(int i = start; i <= n; i += d, ++m)
        {
            pref[d][start][0][m] = pref[d][start][0][m - 1] + m * vec[i];
            pref[d][start][1][m] = pref[d][start][1][m - 1] + vec[i];
        }
    };
    for(int i = 0; i < q; ++i)
    {
        int ss, dd, kk;
        cin >> ss >> dd >> kk;
        r[i] = {ss, dd, kk};
        int start = (ss % dd == 0) ? dd : ss % dd;
        makePref(dd, start);
    }
    // for(auto& [d, st] : mp)
    // {
    //     for(auto& start : st)
    //     {
    //         pref[d][start].assign(2, vector<ll>(n / d + 2, 0));
    //         ll m = 1;
    //         for(int i = start; i <= n; i += d, ++m)
    //         {
    //             pref[d][start][0][m] = pref[d][start][0][m - 1] + m * vec[i];
    //             pref[d][start][1][m] = pref[d][start][1][m - 1] + vec[i];
    //         }
    //     }
    // }

    for(auto& rq : r)
    {
        int ost = (rq.s % rq.d == 0) ? rq.d : rq.s % rq.d;
        
        int start = rq.s / rq.d + int((rq.s % rq.d) != 0);

        // cout << "d = " << rq.d << ", ost = " << ost << ", start = " << start << ", finish = " << start + rq.k - 1 << ": ";

        cout << (pref[rq.d][ost][0][start + rq.k - 1] - pref[rq.d][ost][0][start - 1] - (pref[rq.d][ost][1][start + rq.k - 1] - pref[rq.d][ost][1][start - 1]) * (start - 1)) << " ";
    }
    cout << endl;
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