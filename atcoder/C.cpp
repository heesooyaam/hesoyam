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
    string s;
    cin >> s;
    vector<char> alph(26 + 1);
    for(int i = 0; i + 'a' <= 'z'; ++i)
    {
        alph[i] = i + 'a';
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i)
    {
        char from, to;
        cin >> from >> to;
        for(int j = 0; j + 'a' <= 'z'; ++j)
        {
            if(alph[j] == from) alph[j] = to;
        }
    }
    for(int i = 0; i < n; ++i)
    {
        s[i] = alph[s[i] - 'a'];
    }
    cout << s << endl;
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