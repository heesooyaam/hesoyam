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
    string s;
    cin >> s;
    if(s.find('0') != string::npos)
    {
        cout << "YES\n0\n";
        return;
    }
    for(int i = s.size() - 1; i >= 0; --i)
    {
        if(s[i] == '8'){
            cout << "YES\n";
            cout << 8 << endl;
            return;
        }
        for(int j = i; j >= 0; --j)
        {
            if(i != j && (s[i] - '0' + (s[j] - '0') * 10) % 8 == 0)
            {
                cout << "YES\n";
                cout << s[j] << s[i] << endl;
                return;
            }
            for(int k = j; k >= 0; --k)
            {
                if(i != j && j != k && i != k && (((s[i] - '0') + (s[j] - '0') * 10 + (s[k] - '0') * 100) % 8 == 0))
                {
                    cout << "YES\n";
                    cout << s[k] << s[j] << s[i] << endl;
                    return;
                }
            }
        }
    }
    cout << "NO\n";
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}