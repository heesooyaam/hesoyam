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
struct cell
{
    int r, c;
    ll dist;
    bool operator<(const cell& other) const
    {
        return dist < other.dist;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<string> grid(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> grid[i];
    }
    vector<pair<int, int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<vector<bool>> used(n, vector<bool>(n));
    priority_queue<cell> q;
    q.push({0, 0, 0});
    char curColor;
    curColor = 'R';
    ll ans = 0;
    auto go = [&](int endR, int endC)
    {
        while(!q.empty())
        {
            auto [curR, curC, dist] = q.top();
            q.pop();
            if(used[curR][curC])
            {
                continue;
            }
            else used[curR][curC] = true;
            dist *= -1;
            if(curR == endR && curC == endC)
            {
                ans += dist;
                break;
            }
            for(const auto& [dR, dC] : moves)
            {
                int newR = curR + dR, newC = curC + dC;
                if(0 <= newR && newR < n && 0 <= newC && newC < n && !used[newR][newC])
                {
                    q.push({newR, newC, -1 * (dist + (grid[curR][curC] != curColor))});
                }
            }
        }
    };
    go(n - 1, n - 1);
    while(!q.empty()) q.pop();
    q.push({0, n - 1, 0});
    used.assign(n, vector<bool> (n, false));
    curColor = 'B';
    go(n - 1, 0);
    cout << ans << endl;
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