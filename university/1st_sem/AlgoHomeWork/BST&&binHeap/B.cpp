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
#define endl ' '  

void solve()
{
    int n;
    cin >> n;
    set<int> st;
    map<pair<int, char>, bool> mp;
    int x;
    cin >> x;
    st.insert(x);
    mp[{x, 'r'}] = mp[{x, 'l'}] = false;
    for(int i = 1; i < n; ++i)
    {
        int x;
        cin >> x;
        auto it = st.upper_bound(x);
        if(it == st.end())
        {
            cout << *prev(st.end()) << endl;
            mp[{*prev(st.end()), 'r'}] = true;
        }
        else if(it == st.begin())
        {
            cout << *st.begin() << endl; 
            mp[{*st.begin(), 'l'}] = true;
        }
        else
        {
            if(mp[{*it, 'l'}] == true)
            {
                cout << *(--it) << endl;
                mp[{*it, 'r'}] = true;
            }
            else
            {
                cout << *it << endl;
                mp[{*it, 'l'}] = true;
            }
        }
        st.insert(x);
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}