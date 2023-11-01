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
    int n; ll w;
    cin >> n >> w;
    ll sum = 0;
    queue<int> q;
    bool full = false;

    for(int i = 1; i < n + 1; ++i)
    {
        ll x; cin >> x;
        if(full) continue;
        if(x <= w && x >= w / 2 + w % 2)
        {cout << "1\n" << i << endl; full = true;}
        else if(x < w / 2 + w % 2)
        {
            sum += x;
            q.push(i);
            if(sum >= w/2 + w%2){
                full = true;
                cout << q.size() << endl;
                while(!q.empty())
                {
                    cout << q.front() << ' ';
                    q.pop();
                }
                cout << endl;
            }
        }
    }
    if(!full) cout << -1 << endl;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}