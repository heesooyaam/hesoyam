#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
    vector<pair<int, int>> vec = {mp(7, 3), mp(2, 1), mp(6, 9), mp(3, 3)};
    function<bool(pair<int, int>&, pair<int, int>&)> cmp = [&](pair<int, int>& a, pair<int, int>& b)->bool {return ((a.ff != b.ff) ? a.ff < b.ff : a.ss < b.ss);};
    sort(vec.begin(), vec.end(), cmp);
    for(int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i].ff << ' ' << vec[i].ss << endl;
    }
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}