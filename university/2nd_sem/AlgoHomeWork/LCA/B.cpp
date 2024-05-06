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

int log(int n)
{
    for(int i = 30; i >= 0; --i)
    {
        if(n & (1 << i)) return i + 1;
    }
    return -1;
}
void count(vector<vector<int>>& parent, int cur)
{
    for(int i = 1; i < parent.front().size(); ++i)
    {
        parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
    }
}
void dfs(const vector<vector<int>>& g, vector<vector<int>>& parent, /*vector<int>& path, vector<int>& time,*/ vector<int>& tIn, vector<int>& tOut, int& curTime, int cur)
{
    count(parent, cur);
//    path.eb(cur);
    tIn[cur] = curTime++;
//    time.eb(tIn[cur]);

    for(auto& to : g[cur])
    {
        parent[to][0] = cur;
        dfs(g, parent, /*path, time,*/ tIn, tOut, curTime, to);
    }

    tOut[cur] = curTime++;
//    path.eb(cur);
//    time.eb(tOut[cur]);
}
void solve()
{
    int k;
    cin >> k;

    queue<pair<int, int>> get;
    queue<pair<int, int>> add;

    int n = 1;

    for(int i = 0; i < k; ++i)
    {
        string type;
        int parent, child;
        cin >> type >> parent >> child;

        n = max(n, child);

        if(type.front() == 'G') get.emplace(parent, child);
        else add.emplace(parent, child);
    }

    int logn = log(int(add.size() + 1));

    vector<vector<int>> g(n + 1);
    vector<vector<int>> parent(n + 1, vector<int> (logn + 1, 1));
    vector<int> tIn(n + 1), tOut(n + 1);
//    vector<int> time, path;

    while(!add.empty())
    {
        g[add.front().ff].eb(add.front().ss);
        add.pop();
    }

    int curTime = 0;
    dfs(g, parent, /*path, time,*/ tIn, tOut, curTime, 1);

    auto ancestor = [&](int parent, int child)
    {
        return ((tIn[parent] <= tIn[child]) && (tOut[parent] >= tOut[child]));
    };
    auto LCA = [&](int a, int b)
    {
        auto& mn = (tIn[a] <= tIn[b]) ? a : b;

        if(ancestor(mn, a + b - mn))
        {
            return mn;
        }

        for(int i = logn; i >= 0; --i)
        {
            if(!ancestor(parent[a][i], b))
            {
                a = parent[a][i];
            }
        }

        return parent[a][0];
    };

    while (!get.empty())
    {
        cout << LCA(get.front().ff, get.front().ss) << endl;
        get.pop();
    }
}
int32_t main()
{
    // freopen("lcm.in", "r", stdin);
    // freopen("lcm.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}