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
ll countDif(string& s)
{
    ll ans = 0;
    for(int i = 0; i < s.size() - 1; ++i)
    {
        if(s[i] != s[i + 1]) ++ans;
    }
    return ans;
}   
inline ll go(string& s, int type)
{
    if(s.size() == 1) return 1ll;
    ll ans = 0;
    if(type == 1)
    {
        char cur = s[0];
        int startPos = 0;
        for(int ptr = 1; ptr < s.size(); ++ptr)
        {
            if(cur == s[ptr]) continue;
            else
            {
                ans += 1ll * (ptr - startPos);
                cur = s[ptr];
                startPos = ptr;
            }
        }
    }
    else
    {
        int n = s.size();
        char cur = s[n - 1];
        int startPos = n - 1;
        for(int ptr = n - 2; ptr < s.size(); --ptr)
        {
            if(cur == s[ptr]) continue;
            else
            {
                ans += 1ll * (startPos - ptr);
                cur = s[ptr];
                startPos = ptr;
            }
        }
        return ans;
    }
    return ans + go(s, 2) + s.size() - countDif(s);
}
void solve()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    //bad cases:
    // Xyyyy...yyyy
    // Yxxxx...xxxx
    // yyyy...yyyyX
    // xxxx...xxxxY
    cout << n * (n + 1) / 2 - go(s, 1) << endl;

}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}

// aabaaabb

// total = 36
// len = 8
// type1 = 6
// type2 = 6 
//------------
// ans = 36 - 8 - 6 - 6 = 16

// aaababb

// total = 28
// len = 7
// type1 = 5
// type2 = 6 

// ab