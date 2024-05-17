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
    int n;
    cin >> n;
    vector<unordered_map<char, int>> g(1);
    vector<int> parent(1, 0);
    vector<char> letter(1, '0');
    vector<int> popularity(1, 0);
    ll ans = 0;
    auto addVertex = [&](char ch, int ancestor, int popular)
    {
        g[ancestor][ch] = parent.size();
        g.eb();
        letter.eb(ch);
        popularity.eb(popular);
        parent.eb(ancestor);
        return parent.size() - 1;
    };
    function<void(string&, int, int)> go = [&](string& s, int curTreeIdx, int i)
    {
        if(i == s.size()) return;
        if(g[curTreeIdx].contains(s[i]))
        {
            curTreeIdx = g[curTreeIdx][s[i]];
            ans += popularity[curTreeIdx];
            popularity[curTreeIdx] += 1;
        }
        else
        {
            curTreeIdx = addVertex(s[i], curTreeIdx, 1);
        }
        go(s, curTreeIdx, i + 1);
    };
    for(int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        go(s, 0, 0);
    }
    cout << ans << endl;
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
