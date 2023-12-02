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
    ifstream in("exam.in");
    ofstream out("exam.out");
    set<int> st;
    for(int i = 1; i <= 200'001; ++i)
    {
        st.insert(i);
    }
    int n;
    in >> n;
    while(n--)
    {
        int a; in >> a;
        if(a > 0)
        {
            auto it = st.lower_bound(a);
            if(it != st.end())
            {
                out << *it << endl;
                st.erase(it);
            }
        }
        else st.insert(a * -1);
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}