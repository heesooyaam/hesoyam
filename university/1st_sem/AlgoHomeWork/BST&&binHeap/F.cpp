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
const int INF = INT_MAX;
void solve()
{
    int n;
    cin >> n;

    vector<bool> root(n + 1, true);
    root[0] = 0;
    unordered_map<int, int> cnt;
    vector<int> idxToValue(n + 1);
    vector<pair<int, int>> graf(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        int x, l, r;
        cin >> x >> l >> r;
        graf[i] = {l, r};
        idxToValue[i] = x;
        ++cnt[x];
        for(int q : {l, r})
        {
            if(q != -1) root[q] = false;
        }
    }
    assert(count(all(root), 1) == 1);

    int rt = find(all(root), 1) - root.begin();
    // cout <<"root = " << rt << endl;

    unordered_set<int> ans;

    function<void(int, int, int)> dfs = [&](int cur, int l, int r)->void
    {
        // cout << "curNum = " << idxToValue[cur] << ", [l, r] = [" << l << ", " << r << "]" << endl;
        if(idxToValue[cur] <= r && idxToValue[cur] >= l)
        {
            ans.insert(idxToValue[cur]);
        }

        if(graf[cur].ff != -1) dfs(graf[cur].ff, l, min(r, idxToValue[cur]));    
        if(graf[cur].ss != -1) dfs(graf[cur].ss, max(l, idxToValue[cur]), r);   
    };
    dfs(rt, -INF, INF);
    /*
    cout << "amount of ok nums = " << ans.size() << endl << "here they are: ";
    for(auto& x : ans) cout << x << ' ';
    cout << endl;
    */
    int amount = 0;

    for(auto& [num, c] : cnt)
    {
        if(ans.contains(num)) continue;
        else amount += c;
    }
    cout << amount << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}