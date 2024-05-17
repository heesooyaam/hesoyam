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
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
    }
    unordered_map<int, pair<int, int>, custom_hash> dp;
    vector<int> prev(n, -1);
    int ans = 1;
    int num = 0;
    for(int i = 0; i < n; ++i)
    {
        auto it = dp.find(vec[i]);
        if(it == dp.end())
        {
            dp[vec[i]] = {1, i};
        }
        auto cur = dp.find(vec[i]);
        auto it2 = dp.find(vec[i] - 1);
        if(it2 != dp.end())
        {
            int len = it2->ss.ff + 1;
            if(ans < len)
            {
                ans = len;
                num = i;
            }
            if(cur->ss.ff < len)
            {
                cur->ss = {len, i};
                prev[i] = it2->ss.ss;
            }
        }
    }
    vector<int> arr;
    do
    {
        arr.pb(num + 1);
        num = prev[num];
    }
    while(num != -1);
    reverse(all(arr));
    cout << arr.size() << endl;
    print(arr);
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