#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define endl '\n'   

void solve()
{
    int n, time;
    cin >> n >> time;
    vector <int> book (n);
    input(book);
    vector <int> pref (n + 1);
    for(int i = 1; i <= n; i++)
    {
        pref[i] = pref[i - 1] + book[i - 1];
    }
    // cout << endl;
    // print(pref);
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int idx = upper_bound(all(pref), time + pref[i]) - pref.begin();
        idx -= 2;
        //cout << "book: "<< i << " - idx: " << idx << endl;
        ans = max(ans, idx - i + 1);
    }
    cout << ans<< endl;
}   
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}