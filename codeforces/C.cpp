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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].pb(to);
        g[to].pb(from);
    }

    int root;
    for(int i = 1; i < n + 1; ++i)
    {
        if(g[i].size() == 1)
        {
            root = i;
            break;
        }
    }
    
    int l = 1; int r = n / (k + 1) + 1;
    function<int(int&, int, int, int)> dfs = [&](int& cnt, int cur, int prev, int x)->int
    {
        int size = 1;
        for(auto& to : g[cur])
        {
            if(to == prev) continue;
            int childs = dfs(cnt, to, cur, x);
            if(childs >= x)
            {
                ++cnt;
            }
            else
            {
                size += childs;
            }
        }
        return size;
    };

    while(l + 1 < r)
    {
        int mid = (l + r) / 2;
        int cnt = 0;
        cnt += dfs(cnt, root, -1, mid) >= mid;
        if(cnt < k + 1)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }
    cout << l << endl;
    
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