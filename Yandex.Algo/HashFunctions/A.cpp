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
vector <ll> prefHashX;
vector <ll> powX;
vector <ll> prefHashY;
vector <ll> powY;
vector <ll> prefHashZ;
vector <ll> powZ;
vector <ll> prefHashD;
vector <ll> powD;
const ll X = 31;
const ll Y = 991;
const ll Z = 291;
const ll D = 257;
const ll xMOD = 1'000'000'007;
const ll yMOD = 1'000'000'029;
const ll zMOD = 1'000'000'013;
const ll dMOD = 1'000'000'129;
ll l, a, b;
// inline ll toNum (const char& ch)
// {
//     return (ll) (ch);
// }
inline void createHash(vector<ll>& prefHash, vector<ll>& pow, const ll& mod, const ll& point)
{
    for(int i = 1; i < s.size(); ++i)
    {
        prefHash[i] = ((prefHash[i - 1] * point) % mod + ((ll) s[i] - 'a' + 1)) % mod;
        pow[i] = pow[i - 1] * point;
        pow[i] %= mod;
    }
}
bool checkH(vector<ll>& prefHash, vector<ll>& pow, const ll& mod)
{
    return (prefHash[a + l - 1] + (prefHash[b - 1] * pow[l]) % mod) % mod == (prefHash[b + l - 1] + (prefHash[a - 1] * pow[l]) % mod) % mod;
}
void solve()
{
    cin >> l >> a >> b;
    ++a;
    ++b;
    if(checkH(prefHashX, powX, xMOD) && checkH(prefHashY, powY, yMOD) && checkH(prefHashZ, powZ, zMOD) && checkH(prefHashD, powD, dMOD))
    {
        cout << "yes\n";
    }
    else
    {
        cout << "no\n";
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    string q;
    cin >> q;
    s += q;
    int n = s.size() - 1 ;

    prefHashX.assign(n + 1, 0);
    powX.assign(n + 1, 1);

    prefHashY.assign(n + 1, 0);
    powY.assign(n + 1, 1);

    prefHashZ.assign(n + 1, 0);
    powZ.assign(n + 1, 1);

    prefHashD.assign(n + 1, 0);
    powD.assign(n + 1, 1);

    createHash(prefHashX, powX, xMOD, X);
    createHash(prefHashY, powY, yMOD, Y);
    createHash(prefHashZ, powZ, zMOD, Z);
    createHash(prefHashD, powD, dMOD, D);

    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}