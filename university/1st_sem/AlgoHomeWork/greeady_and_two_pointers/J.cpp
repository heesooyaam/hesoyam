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
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define print(x); for(auto& val : x) {cout << val << ' ';} cout << endl;
#define input(x); for(auto& val : x) {cin >> val;}
#define endl '\n'   
void solve()
{
    int n; cin >> n;
    vector <int> k (n);
    input(k);
    vector <int> FH (n / 2);
    vector <int> SH (n - n / 2);
    sort(all(k));
    int fill = 0;
    for(; fill < n / 2; fill++)
    {
        FH[fill] = k[fill];
    }
    for(int i = 0; fill < n; fill++)
    {
        SH[i++] = k[fill];
    }

    int cnt = 0;
    for(int fst = 0, snd = 0; fst < FH.size(); fst++)
    {
        for(; snd < SH.size() && FH[fst] * 2 > SH[snd]; snd++){}
        if(snd == SH.size()) break;
        else{
            cnt++;
            snd++;
        }
    }
    cout << n - cnt << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}

// x = 1;
//1: int y = x++; -> y = 1, x = 2
//2:int y = ++x; -> y = 2; x = 2; 