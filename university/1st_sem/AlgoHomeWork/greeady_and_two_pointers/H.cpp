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
    int n, k; cin >> n >> k;
    vector <int> pos (n + 1);
    for(int i = 0; i < n; i++)
    {
        int num; cin >> num;
        pos[num] = i;
    }
    vector <int> l(n, -1);
    for(int i = 0; i < k; i++)
    {
        int p1, p2;
        cin >> p1 >> p2;
        p1 = pos[p1]; p2 = pos[p2];
        if(p1 > p2) swap(p1, p2);
        l[p2] = max(l[p2], p1);
    }
    int mxL = -1;
    ll ans = 0;
    for(int r = 0; r < n; r++)
    {
        mxL = max(mxL, l[r]);
        ans += 1ll * r - mxL;
    }

    cout << ans << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}