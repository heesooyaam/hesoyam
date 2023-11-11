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
string s = " ";
const ll modX = 1'000'000'007;
const ll modY = 1'000'000'123;
const ll modZ = 1'000'000'009;
const ll x = 31;
const ll y = 291;
const ll z = 257;
inline void createHash(vector<ll>& prefHash, vector<ll>& pow, const ll& mod, const ll& point)
{
    for(int i = 1; i < s.size(); ++i)
    {
        prefHash[i] = ((prefHash[i - 1] * point) % mod + ((ll) s[i] - 'a' + 1)) % mod;
        pow[i] = pow[i - 1] * point;
        pow[i] %= mod;
    }
}
bool checkH(vector<ll>& prefHash, vector<ll>& pow, const ll& mod, int a, int b, int l)
{
    return ((prefHash[a + l - 1] + (prefHash[b - 1] * pow[l]) % mod) % mod) == ((prefHash[b + l - 1] + (prefHash[a - 1] * pow[l]) % mod) % mod);
}
void solve()
{
    string q;
    cin >> q;
    int n = q.size();
    s += q;
    vector<ll> prefHashX(n + 1);
    vector<ll> powX(n + 1, 1);
    createHash(prefHashX, powX, modX, x);
    vector<ll> prefHashY(n + 1);
    vector<ll> powY(n + 1, 1);
    createHash(prefHashY, powY, modY, y);
    vector<ll> prefHashZ(n + 1);
    vector<ll> powZ(n + 1, 1);
    createHash(prefHashZ, powZ, modZ, z);
    ll ans = INT_MAX;
    for(int l = 0; l < n; ++l)
    {
        int a = 1, b = n - l + 1;
        if(checkH(prefHashX, powX, modX, a, b, l) && checkH(prefHashY, powY, modY, a, b, l) && checkH(prefHashZ, powZ, modZ, a, b, l))
        {
            ans = n - l;
        }
    }
    
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}