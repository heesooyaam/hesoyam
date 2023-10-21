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

void solve(vector <string>& lib)
{
    string word;
    cin >> word;
    cout << upper_bound(all(lib), word) - lib.begin() << endl;
}

int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    vector <string> lib(650);
    int idx = 0;
    for(char fst = 'a'; fst <= 'z'; ++fst)
    {
        for(char snd = 'a'; snd <= 'z'; ++snd)
        {
            if(fst == snd) continue;
            
            lib[idx] += fst;
            lib[idx++] += snd;
        }
    }
    //print(lib);
    int t = 1; cin >> t;
    while(t--) solve(lib);
    return 0;
}