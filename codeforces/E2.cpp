#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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
    int n;
    cin >> n;
    vector<vector<ll>> ball(2, vector<ll> (n + 1));
    for(int q : {0, 1})
    {
        for(int i = 1; i <= n; ++i)
        {
            cin >> ball[q][i];
        }
    }
    ll A = 0, B = 0;
    set<pair<ll, ll>, greater<>> stA;
    set<pair<ll, ll>, greater<>> stB;
    for(int i = 1; i < n + 1; ++i)
    {
        if(ball[0][i] != 0 && ball[1][i] != 0)
        {
            stA.insert({ball[0][i] + ball[1][i] - 1, i});
            stB.insert({ball[0][i] + ball[1][i] - 1, i});
        }
        A += ball[0][i];
        B += ball[1][i];
    }
    int step = 0;
    while(!stA.empty())
    {
        if(step == 0)
        {
            auto p = *stA.begin();
            stB.erase(p);
            A--;
            B -= ball[step ^ 1][p.ss];
            stA.erase(stA.begin());
        }
        else
        {
            auto p = *stB.begin();
            stA.erase(p);
            B--;
            A -= ball[step ^ 1][p.ss];
            stB.erase(stB.begin());
        }
        step ^= 1;
    }
    cout << A - B << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}