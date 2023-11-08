#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define endl '\n'   

void solve()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    vector <pair<int, int>> knight (n);
    vector <pair<int, int>> armor (m);
    for(int i = 0; i < n; i++)
    {
        cin >> knight[i].first;
        knight[i].second = i + 1;
    }
    for(int i = 0; i < m; i++)
    {
        cin >> armor[i].first;
        armor[i].second = i + 1;
    }
    // sort(all(wish));
    // sort(all(real));
    vector<pair<int, int>> ans;
    for(int k = 0, l = 0, r = 0, a = 0; k < n; k++)
    {
        for(; r < m && armor[r].first <= knight[k].first + y; r++){}
        for(; l < r && armor[l].first < knight[k].first - x; l++){}
        if(l < r)
        {
            ans.eb(knight[k].second, armor[l++].second);
        }
    }
    cout << ans.size() << endl;
    for(auto& [numP, numA] : ans) cout << numP << ' ' << numA << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}

// 4 4 1 1
// 5 5 6 7
// 10 11 12 13