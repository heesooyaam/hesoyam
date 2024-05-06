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
//#define int int64_t

template<typename T>
class SparceTable
{
public:
    SparceTable(const vector<T>& vec)
    : n(vec.size() + 1)
    , power(__lg(n) + 1)
    , table(power, vector<T> (n, numeric_limits<T>::max()))
    {
        build(vec);
    }
    T getMin(int l, int r) const
    {
        assert(r - l + 1 > 0);
        int p = __lg(r - l + 1);
        return ((table[p][l] < table[p][r - (1 << p) + 1]) ? table[p][l] : table[p][r - (1 << p) + 1]);
    }
private:
    const size_t n;
    const size_t power;
    vector<vector<T>> table;
    void build(const vector<T>& vec)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            table[0][i] = vec[i];
        }
        for(int p = 0; p < power - 1; ++p)
        {
            for(int i = 0; i + (1 << (p + 1)) < n; ++i)
            {
                table[p + 1][i] = (table[p][i] < table[p][i + (1 << p)]) ? table[p][i] : table[p][i + (1 << p)];
            }
        }
    }
};
void dfs(const vector<vector<int>>& g, vector<int>& path, vector<int>& time, vector<int>& tIn, vector<int>& tOut, int& curTime, int cur)
{
    tIn[cur] = curTime++;

    path.eb(cur);
    time.eb(tIn[cur]);

    for(auto& to : g[cur])
    {
        dfs(g, path, time, tIn, tOut, curTime, to);
        ++curTime;
        time.eb(tIn[cur]);
        path.eb(cur);
    }

    tOut[cur] = curTime++;

    path.eb(cur);
    time.eb(tIn[cur]);
}
void solve()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);
    vector<int> tIn(n), tOut(n);
    vector<int> time, path;

    for(int i = 1; i < n; ++i)
    {
        int parent;
        cin >> parent;
        assert(parent <= n);
        g[parent].eb(i);
    }

    int curTime = 0;
    dfs(g, path, time, tIn, tOut, curTime, 1);

    SparceTable<int> ST(time);
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

        int l = tOut[mn];
        int r = tIn[a + b - mn];

        return path[ST.getMin(l, r)];
    };


    ll sum = 0;
    for(ll i = 0, _a, _b, x, y, z, _ans; i < m; ++i)
    {
        if(i)
        {
            ll a, b;
            a = (_a * x + _b * y + z) % n;
            b = (_b * x + a * y + z) % n;
            _ans = LCA((a + _ans) % n, b);
            _a = a;
            _b = b;
        }
        else
        {
            cin >> _a >> _b >> x >> y >> z;
            _ans = LCA(_a, _b);
//          cout << _ans - 1 << endl;
        }
        sum += _ans;
    }
    cout << sum << endl;
}
int32_t main()
{
    // freopen("lca_rmq.in", "r", stdin);
    // freopen("lca_rmq.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}