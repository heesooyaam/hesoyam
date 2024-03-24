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
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        int x, y;
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }

    vector<int> parent(n + 1, 0);
    vector<int> dist(n + 1, -1);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(auto& to : g[cur])
        {
            if(dist[to] != -1) continue;

            parent[to] = cur;
            dist[to] = dist[cur] + 1;
            q.push(to);
        }
    }

    vector<int> vec(n); // sequence
    vector<int> check(n); // parent of vec[0], parent of vec[1], ...
    vector<int> time(n + 1, 0); // idx of vec[i] in vec
    time[0] = -1;

    set<int> st;

    for(int i = 0; i < n; ++i)
    {
        cin >> vec[i];
        time[vec[i]] = i;
        check[i] = parent[vec[i]];
        st.insert(check[i]);
    }
    for(int i = 1; i < n; ++i)
    {
        if(check[i - 1] != check[i] && time[check[i - 1]] > time[check[i]])
        {
            cout << "No\n";
            return;
        }
    }
    check.resize(unique(all(check)) - check.begin());
    if(st.size() != check.size())
    {
        cout << "No\n";
        return;
    }
    for(int i = 1; i < n; ++i)
    {
        if(dist[vec[i]] < dist[vec[i - 1]])
        {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}