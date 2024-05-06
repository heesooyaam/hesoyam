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
    int k;
    cin >> k >> k;
    string s;
    cin >> s;
    auto count = [&](const string& temp)
    {
        ll res = 0;
        for(int i = 0; i < n;)
        {
            if(s[i] != temp.front())
            {
                ++i;
                continue;
            }
            int cur = i;
            int j = 0;
            for(; cur < s.size() && j < temp.size();)
            {
                if(s[cur] == temp[j])
                {
                    ++cur; ++j;
                }
                else break;
            }
            if(j == temp.size())
            {
                i = cur;
                ++res;
            }
            else
            {
                ++i;
            }
        }
        return res;
    };
    int l = 0; int r = n / k;
    while(l + 1 < r)
    {
        int mid = (l + r) >> 1;
        if(count(s.substr(0, mid)) >= k)
        {
            l = mid;
        }
        else r = mid - 1;
    }
    if(count(s.substr(0, r)) >= k)
    {
        cout << r << endl;
    }
    else cout << l << endl;
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