#include <bits/stdc++.h>
using namespace std;

// example from graph contest:
// В первой строке вам даны два числа n и m — количество пакетов и зависимостей между ними.
// В следующих m строках описаны зависимости между пакетами в виде пар чисел u и v, которые означают, что для установки пакета v, нужен пакет u

#include <bits/stdc++.h>
using namespace std;
#define ll long 
#define ull unsigned long 
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define endl '\n'   

void dfs(vector<vector <int>>& g, vector<bool>& installed, vector <int>& ans, int cur, int from)
{
    for(int& to : g[cur])
    {
        if(installed[to]) continue;
        if(to == from) continue;
        dfs(g, installed, ans, to, cur);
    }

    ans.eb(cur);
    installed[cur] = true;

    return;
}

void solve()
{
    int n, m; cin >> n >> m;
    vector <vector<int>> graf (n + 1);
    while(m--)
    {
        int from, to; cin >> from >> to;
        graf[from].eb(to);
    }
    vector <bool> installed (n + 1);
    vector <int> ans;

    for(int p = 1; p <= n; p++)
    {
        if(installed[p]) continue;
        int from = -1;
        dfs(graf, installed, ans, p, from);
    }
    
    for(int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i] << ' ';
    }
}   
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}