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

void solve()
{
    ull n;
    cin >> n;
    // C(n/2, n) * ((n/2 - 1)!)^2 / 2
    int cnt = 0;
    ull factN2 = 1;
    while(cnt++ < n / 2 - 1)
    {
        factN2 *= cnt;
    }
    ull factN = factN2 * n / 2;
    while(cnt++ < n)
    {
        factN *= cnt;
    }
    //cout << "n! = " << factN << "\n(n/2 - 1)! = " << factN2 << "\n(n/2)! = " << (factN2 * n / 2) << endl;
    cout << (factN / (factN2 * n / 2) / (factN2 * n / 2)) / 2 * factN2 * factN2 << endl; 
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    while(t--) solve();
    return 0;
}