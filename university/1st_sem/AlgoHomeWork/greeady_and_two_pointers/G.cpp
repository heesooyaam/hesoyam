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
#define endl '\n'   

void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    map <char, int> cur;
    for(char& ch : s)
    {
        cur[ch] = -1;
    }
    //cout << cur.size() << endl;
    int mn = 1e9;
    int cnt = 0;
    int ptr1, ptr2; ptr1 = ptr2 = 0;
    int last = -1;
    for(; ptr1 < s.size(); ptr1++)
    {
        for(; ptr2 < s.size(); ptr2++)
        {
            if(ptr2 != last and ++cur[s[ptr2]] == 0) cnt++;
            //cout << "cnt/cur len: " << cnt << ' ' << ptr2 - ptr1 + 1 << endl;
            if(cnt == cur.size())
            {
                mn = min(ptr2 - ptr1 + 1, mn);
                break;
            } 
        }
        last = ptr2;
        if(--cur[s[ptr1]] == -1) --cnt;
        // for(auto& [ch, k] : cur)
        // {
        //     cout << ch << ": " << k << endl;
        // }
        //cout<< "cnt: " << cnt << endl << endl;
    }
    cout << mn << endl;


}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}