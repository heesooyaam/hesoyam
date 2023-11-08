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
    int n, a, b; // a - white, b - black
    cin >> n >> a >> b;
    vector <int> vec (n);
    for(int i = 0; i < n; i++)
    {
        cin >> vec[i];
    }
    ll sum = 0;
    for(int i = 0; i < n / 2; i++)
    {
        if(vec[i] + vec[n - 1 - i] == 4)
        {
            sum += 2 * min(a, b);
        }
        else if((vec[i] + vec[n - 1 - i] == 2 and vec[i] * vec[n - 1 - i] != 0) or vec[i] + vec[n - 1 - i] == 0)
        {
            continue;
        }
        else if(vec[i] + vec[n - 1 - i] == 1)
        {
            cout << -1 << endl;
            return;
        }
        else
        {
            int cur = min(vec[i], vec[n - 1 - i]);
            sum += (cur == 0) * a + (cur == 1) * b;
        }
    }

    if(n % 2 && vec[n / 2] == 2) sum += min(a, b);
    cout << sum << endl; 
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}