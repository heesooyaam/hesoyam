#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
//0 0 1 1 0 0 1 1 0 1 0 0 1 0
void solve()
{
    int n; cin >> n;
    vector <int> choco(n);
    input(choco);
    int nuts = count(all(choco), 1);
    ll ans = 1;
    if(nuts == 1)
    {
        cout << ans << endl;
        return;
    }
    if(nuts == 0)
    {
        cout << 0 << endl;
        return;
    }
    for(int i = 0, cnt = 0, cur = 0; i < n; ++i)
    {
        if(cnt > 0 && cnt < nuts)
        {
            if(choco[i])
            {
                ans *= 1ll * (cur + 1);
                cur = 0;
            }
            else ++cur;
        }
        cnt += choco[i];
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