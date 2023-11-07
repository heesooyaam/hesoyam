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

int go(vector<vector<int>>& graf, vector<int>& dist, int cur, int prev)
{
    if(dist[cur] != -1) return dist[cur] + 1;
    else dist[cur] = 0;

    for(auto& to : graf[cur])
    {
        if(to == prev) continue;

        dist[cur] = max(dist[cur], go(graf, dist, to, cur));
    }

    return dist[cur] + 1;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> p (k, vector<int> (n));
    vector<vector<int>> pos(k, vector<int> (n + 1));
    for(int i = 0; i < k; ++i)
    {
        input(p[i]);
    }
    for(int q = 0; q < k; ++q){
        for(int i = 0; i < n; ++i)
        {
            pos[q][p[q][i]] = i;
        }
    }
    vector<vector<int>> graf(n + 1);
    for(int num = 1; num <= n; ++num)
    {
        for(int post = 1; post <= n; ++post)
        {
            if(num == post) continue;
            bool ok = true;
            for(int i = 0; i < k && ok; ++i)
            {
                if(pos[i][num] > pos[i][post]) ok = false;
            }
            if(ok)
            {
                graf[num].pb(post);
            }
        }
    }
    // cout << endl;
    // for(int i = 1; i <= n; ++i)
    // {
    //     cout << i << " : ";
    //     print(graf[i]);
    // }
    // cout << endl;
    vector<int> dist(n + 1, -1);
    for(int i = 1; i <= n; ++i)
    {
        if(dist[i] == -1) go(graf, dist, i, -1);
    }
    //cout << "dist: ";
    //print(dist)
    cout << *max_element(all(dist)) + 1 << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}