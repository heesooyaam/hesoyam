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
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   

void solve()
{
    int n, k, p, x, y; // x - sum, y - mid
    cin >> n >> k >> p >> x >> y;
    vector <int> vec (n);
    ll sum = 0;
    int cnt = 0;
    for(int i = 0; i < k; i++)
    {
        int x; cin >> x;
        sum += x;
        cnt += (bool) (x >= y);
    }
    if(k - cnt > (n - 1) / 2)
    {
        cout << -1 << endl;
        return;
    }
    int need = (n + 1) / 2;
    if(cnt < need)
    {
        if(n - k < need - cnt)
        {
            cout << -1 << endl;
            return;
        }
        else
        {
            sum += (need - cnt) * y;
        }
    }
    else need = cnt;

    int ost = n - k - (need - cnt);

    if(sum + ost > x )
    {
        cout << -1 << endl;
        return;
    }
    for(int i = 0; i < need - cnt; i++)
    {
        cout << y << ' ';
    }
    for(int i = 0; i < ost; i++)
    {
        cout << 1 << ' ';
    }
    cout << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}