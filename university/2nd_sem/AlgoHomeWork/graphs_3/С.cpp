//
// Created by topcr on 28.03.2024.
//
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
// a -> b => label_a < label_b
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n + 1);
    vector<vector<int>> transp_g(n + 1);
    for(int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].insert(to);
        transp_g[to].eb(from);
    }
    set<int, greater<int>> st;
    for(int i = 1; i < n + 1; ++i)
    {
        if(g[i].size() == 0)
        {
            st.insert(i);
        }
    }
    vector<int> p(n);
    for(int i = n; i >= 1; --i)
    {
        int cur = *st.begin();
        st.erase(st.begin());
        p[cur - 1] = i;
        for(auto& parent : transp_g[cur])
        {
            g[parent].erase(cur);
            if(g[parent].size() == 0) st.insert(parent);
        }
    }
    print(p);
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}