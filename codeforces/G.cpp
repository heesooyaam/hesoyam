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
    input(vec);
    unordered_map<int, pair<priority_queue<int, vector<int>, greater<>>, vector<int>>, custom_hash> mapa;
    for(int i = 0; i < n; ++i)
    {
        auto it = mapa.find(vec[i] >> 2);
        if(it != mapa.end())
        {
            it->ss.ff.push(vec[i]);
            it->ss.ss.pb(i);
        }
        else
        {
            mapa[vec[i] >> 2] = {{}, {i}};
            mapa[vec[i] >> 2].ff.push(vec[i]);
        }

    }
    for(auto& [_, pair] : mapa)
    {
        auto& [nums, idx] = pair;
        for(int i = 0; i < idx.size(); ++i)
        {
            vec[idx[i]] = nums.top();
            nums.pop();
        }
    }
    print(vec);
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